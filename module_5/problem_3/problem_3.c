#include <linux/tty.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kd.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/vt.h>
#include <linux/vt_kern.h>
#include <linux/console_struct.h>

#define BLINK_DELAY HZ / 5
#define ALL_LEDS_ON 0x7
#define RESTORE_LEDS 0xFF

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bukha");
MODULE_DESCRIPTION("problem_2");

static struct kobject *example_kobject;
static struct timer_list my_timer;
static struct tty_driver *my_driver;
static int kbledstatus = 0;
static int value = 0;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", value);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    sscanf(buf, "%du", &value);
    return count;
}

static void my_timer_func(struct timer_list *unused) {
    struct tty_struct *t = vc_cons[fg_console].d->port.tty;

    if (kbledstatus == value)
        kbledstatus = RESTORE_LEDS;
    else
        kbledstatus = value;

    (my_driver->ops->ioctl)(t, KDSETLED, kbledstatus);

    my_timer.expires = jiffies + BLINK_DELAY;
    add_timer(&my_timer);
}

static int kbleds_init(void) {
    size_t i;
    pr_info("kbleds: loading\n");
    pr_info("kbleds: fgconsole is %x\n", fg_console);
    for (i = 0; i < MAX_NR_CONSOLES; ++i) {
        if (!vc_cons[i].d)
            break;
        pr_info("poet_atkm: console[%i/%i] #%i, tty %lx\n", i, MAX_NR_CONSOLES, vc_cons[i].d->vc_num, (unsigned long)vc_cons[i].d->port.tty);
    }
    pr_info("kbleds: finished scanning consoles\n");

    my_driver = vc_cons[fg_console].d->port.tty->driver;
    pr_info("kbleds: tty driver name %x\n", my_driver->name);

    timer_setup(&my_timer, my_timer_func, 0);

    my_timer.expires = jiffies + BLINK_DELAY;
    add_timer(&my_timer);
    return 0;
}

static void kbleds_cleanup(void) {
    pr_info("kbleds: unloading...\n");
    del_timer(&my_timer);
    (my_driver->ops->ioctl)(vc_cons[fg_console].d->port.tty, KDSETLED, RESTORE_LEDS);
}

static struct kobj_attribute foo_attribute = __ATTR(value, 0660, foo_show, foo_store);

static int __init led_init(void) {
    int error = 0;

    pr_info("Module initialized successfully \n");

    example_kobject = kobject_create_and_add("sys_test", kernel_kobj);
    if (!example_kobject){
	pr_info("eror kobject_create_and_add \n");
        return 1;
    }
    if ((error = sysfs_create_file(example_kobject, &foo_attribute.attr))) {
        pr_info("failed to create the foo file in /sys/kernel/sys_test \n");
        return error;
    }
    return error;
}

static void __exit exit_module(void) {
    pr_info("Module un initialized successfully \n");
    kbleds_cleanup();
    kobject_put(example_kobject);
}

module_init(led_init);
module_exit(exit_module);
