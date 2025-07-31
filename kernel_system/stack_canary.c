#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
unsigned long __stack_chk_guard;

static void set_stack_canary(void) {
    get_random_bytes(&__stack_chk_guard, sizeof(__stack_chk_guard));
}

static int __init stack_canary_init(void) {
    set_stack_canary();
    return 0;
}

static void __exit stack_canary_exit(void) {}

module_init(stack_canary_init);
module_exit(stack_canary_exit);
MODULE_LICENSE("GPL"); 