#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define PROC_NAME "test"
#define MSG_SIZE 500

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bukha");
MODULE_DESCRIPTION("problem_2");


static int len = 0, temp = 0;
static char *msg;

static ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp);

static ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp);

static ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp) {
    if (count > temp) {
        count = temp;
    }
    temp = temp - count;
    if (copy_to_user(buf, msg, count)) {
	printk(KERN_ERR "error copy_to_user");
        return 1;
    }

    if (count == 0)
        temp = len;
    return count;
}

static ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp) {
    if (copy_from_user(msg, buf, count)) {
	printk(KERN_ERR "error copy_from_user");
        return 1;
    }
    len = count;
    temp = len;
    return count;
}

static const struct proc_ops proc_fops = {
    .proc_read = read_proc,
    .proc_write = write_proc,
};

static void create_new_proc_entry(void) { 
    proc_create(PROC_NAME, 0666, NULL, &proc_fops);
    msg = kmalloc(MSG_SIZE * sizeof(char), GFP_KERNEL);
    if(msg == NULL){
       printk(KERN_ERR "error kmalloc");
       return;
    }
}

static int proc_init(void) {
    create_new_proc_entry();
    return 0;
}

static void proc_cleanup(void) {
    remove_proc_entry(PROC_NAME, NULL);
    kfree(msg);
}

module_init(proc_init);
module_exit(proc_cleanup);
