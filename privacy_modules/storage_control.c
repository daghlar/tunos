#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/sysfs.h>

#define MAX_PROFILES 8
#define MAX_APPS 128
static int storage_access_enabled[MAX_PROFILES][MAX_APPS] = {{0}};
EXPORT_SYMBOL(storage_access_enabled);

static ssize_t storage_access_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    int p, i, len = 0;
    for (p = 0; p < MAX_PROFILES; p++) {
        for (i = 0; i < MAX_APPS; i++)
            len += sprintf(buf + len, "%d ", storage_access_enabled[p][i]);
        if (len > 0)
            buf[len - 1] = '\n';
    }
    return len;
}

static ssize_t storage_access_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    int profile_id, app_id, value;
    if (sscanf(buf, "%d %d %d", &profile_id, &app_id, &value) == 3) {
        if (profile_id >= 0 && profile_id < MAX_PROFILES && app_id >= 0 && app_id < MAX_APPS)
            storage_access_enabled[profile_id][app_id] = value ? 1 : 0;
    }
    return count;
}

static struct kobj_attribute storage_access_attribute =
    __ATTR(storage_access, 0660, storage_access_show, storage_access_store);

static struct kobject *storage_kobj;

static int __init storage_control_init(void) {
    storage_kobj = kobject_create_and_add("storage_control", kernel_kobj);
    if (!storage_kobj)
        return -ENOMEM;
    return sysfs_create_file(storage_kobj, &storage_access_attribute.attr);
}

static void __exit storage_control_exit(void) {
    kobject_put(storage_kobj);
}

module_init(storage_control_init);
module_exit(storage_control_exit);
MODULE_LICENSE("GPL");
