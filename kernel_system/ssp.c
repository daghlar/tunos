#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
unsigned long __stack_chk_guard;

static int __init ssp_init(void) {
    get_random_bytes(&__stack_chk_guard, sizeof(__stack_chk_guard));
    return 0;
}

static void __exit ssp_exit(void) {}

module_init(ssp_init);
module_exit(ssp_exit);
MODULE_LICENSE("GPL"); 