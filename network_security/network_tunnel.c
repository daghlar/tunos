#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/inet.h>

static struct net_device *tun_dev;

static rx_handler_result_t tunnel_rx_handler(struct sk_buff **pskb) {
    struct sk_buff *skb = *pskb;
    skb->dev = tun_dev;
    return RX_HANDLER_ANOTHER;
}

static int __init network_tunnel_init(void) {
    tun_dev = dev_get_by_name(&init_net, "tun0");
    if (!tun_dev)
        return -ENODEV;
    rtnl_lock();
    netdev_rx_handler_register(tun_dev, tunnel_rx_handler, NULL);
    rtnl_unlock();
    return 0;
}

static void __exit network_tunnel_exit(void) {
    if (tun_dev) {
        rtnl_lock();
        netdev_rx_handler_unregister(tun_dev);
        rtnl_unlock();
        dev_put(tun_dev);
    }
}

module_init(network_tunnel_init);
module_exit(network_tunnel_exit);
MODULE_LICENSE("GPL"); 