#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/gpio.h>

#define BRIGHTNESS_GPIO 23
#define VOLUME_GPIO 24

static int set_brightness(int value) {
    return gpio_direction_output(BRIGHTNESS_GPIO, value);
}

static int set_volume(int value) {
    return gpio_direction_output(VOLUME_GPIO, value);
}

static int __init hardware_control_init(void) {
    gpio_request(BRIGHTNESS_GPIO, "brightness");
    gpio_request(VOLUME_GPIO, "volume");
    set_brightness(1);
    set_volume(1);
    return 0;
}

static void __exit hardware_control_exit(void) {
    gpio_free(BRIGHTNESS_GPIO);
    gpio_free(VOLUME_GPIO);
}

module_init(hardware_control_init);
module_exit(hardware_control_exit);
MODULE_LICENSE("GPL"); 