#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

static struct kobject *settings_kobj;
static int dark_mode = 1;
static int animations = 1;

static ssize_t dark_mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", dark_mode);
}
static ssize_t dark_mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    sscanf(buf, "%d", &dark_mode);
    return count;
}
static ssize_t animations_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", animations);
}
static ssize_t animations_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    sscanf(buf, "%d", &animations);
    return count;
}
static struct kobj_attribute dark_mode_attr = __ATTR(dark_mode, 0660, dark_mode_show, dark_mode_store);
static struct kobj_attribute animations_attr = __ATTR(animations, 0660, animations_show, animations_store);

static int __init system_settings_init(void) {
    settings_kobj = kobject_create_and_add("system_settings", kernel_kobj);
    sysfs_create_file(settings_kobj, &dark_mode_attr.attr);
    sysfs_create_file(settings_kobj, &animations_attr.attr);
    return 0;
}
static void __exit system_settings_exit(void) {
    kobject_put(settings_kobj);
}
module_init(system_settings_init);
module_exit(system_settings_exit);
MODULE_LICENSE("GPL"); 