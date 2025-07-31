#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>

static struct net_device *vpn_dev;

static rx_handler_result_t vpn_rx_handler(struct sk_buff **pskb) {
    struct sk_buff *skb = *pskb;
    skb->dev = vpn_dev;
    return RX_HANDLER_ANOTHER;
}

static int __init vpn_engine_init(void) {
    vpn_dev = dev_get_by_name(&init_net, "vpn0");
    if (!vpn_dev)
        return -ENODEV;
    rtnl_lock();
    netdev_rx_handler_register(vpn_dev, vpn_rx_handler, NULL);
    rtnl_unlock();
    return 0;
}

static void __exit vpn_engine_exit(void) {
    if (vpn_dev) {
        rtnl_lock();
        netdev_rx_handler_unregister(vpn_dev);
        rtnl_unlock();
        dev_put(vpn_dev);
    }
}

module_init(vpn_engine_init);
module_exit(vpn_engine_exit);
MODULE_LICENSE("GPL"); 