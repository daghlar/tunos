#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/security.h>
#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

static int cfi_enforce_task(struct task_struct *task) {
    const struct cred *cred = get_task_cred(task);
    if (cred->uid.val == 0) {
        put_cred(cred);
        return -EPERM;
    }
    put_cred(cred);
    return 0;
}

static int __init cfi_init(void) {
    security_add_hooks(NULL, 0, "tunos_cfi");
    return 0;
}

static void __exit cfi_exit(void) {}

module_init(cfi_init);
module_exit(cfi_exit);
MODULE_LICENSE("GPL"); 