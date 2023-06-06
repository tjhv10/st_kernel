#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "st_kernel"
#define BUF_SIZE 1024

static dev_t dev;
static struct cdev cdev;
static unsigned char *buffer;
static unsigned char key = 0xFA;

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device released\n");
    return 0;
}

static ssize_t device_read(struct file *filp, char __user *buf, size_t len, loff_t *offset) {
    if (len > BUF_SIZE)
        len = BUF_SIZE;

    if (copy_to_user(buf, buffer, len))
        return -EFAULT;

    return len;
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t len, loff_t *offset) {
    if (len > BUF_SIZE)
        len = BUF_SIZE;

    if (copy_from_user(buffer, buf, len))
        return -EFAULT;

    // Perform XOR encryption on the buffer using the key
    for (size_t i = 0; i < len; i++)
        buffer[i] ^= key;

    return len;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

static int __init st_kernel_init(void) {
    int ret;

    // Allocate memory for the buffer
    buffer = kmalloc(BUF_SIZE, GFP_KERNEL);
    if (!buffer)
        return -ENOMEM;

    // Allocate a range of character device numbers
    ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        kfree(buffer);
        return ret;
    }

    // Initialize the character device structure
    cdev_init(&cdev, &fops);
    cdev.owner = THIS_MODULE;

    // Add the character device to the system
    ret = cdev_add(&cdev, dev, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev, 1);
        kfree(buffer);
        return ret;
    }

    printk(KERN_INFO "st_kernel initialized\n");
    return 0;
}

static void __exit st_kernel_exit(void) {
    cdev_del(&cdev);
    unregister_chrdev_region(dev, 1);
    kfree(buffer);
    printk(KERN_INFO "st_kernel removed\n");
}

module_init(st_kernel_init);
module_exit(st_kernel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("XOR Encryption Character Device");
