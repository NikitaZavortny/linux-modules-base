#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <stdio.h>

MODULE_LICENSE("GPL");

struct Config{
	char* license;
	char* author;
	char* name;
};


dev_t dev = 0;

static ssize_t readDRiv(struct file *File, char *UserBuffer, size_t ammount, loff_t *offs)
{
	int ToCopy, NotCopied, Delta;

	ToCopy = min(ammount, BufferSize);
	NotCopied = copy_to_user(UserBuffer, Buffer, ToCopy);
	Delta = ToCopy - NotCopied;

	printk("read is %d", Delta);

	return Delta;
}

static ssize_t writeDRiv(struct file *File, const char *UserBuffer, size_t ammount, loff_t *offs)
{
	int ToCopy, NotCopied, Delta;

	ToCopy = min(ammount, sizeof(Buffer));
	NotCopied = copy_from_user(Buffer, UserBuffer, ToCopy);
	Delta = ToCopy - NotCopied;
	BufferSize = ToCopy;

	printk("write is %d", Delta);

	return Delta;
}

static int openDRiv(struct inode *node, struct file *filee)
{
	printk("opened an openDRiv");
	return 0;
}

static int closeDRiv(struct inode *node, struct file *filee)
{
	printk("closed an openDRiv");
	return 0;
}

static struct file_operations f_ops = {
	.owner = THIS_MODULE,
	.open = openDRiv,
	.write = writeDRiv,
	.read = readDRiv,
	.release = closeDRiv
};

static struct class *MyClass;

static char Buffer [255];
static int BufferSize;

#define DEVICE_NAME "Default Chardev"
#define CLASS_NAME "CUM class"

int Init_chrdev()
{
	int retval = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);

	if(retval < 0)
	{
		printk("Chardev was NOT initialised. Error code: %d", retval);
		return 0;
	}
	else if (retval == 0)
	{
		printk(KERN_ALERT "Chardev was initialised");
		return -1;
	}
	else
	{
		printk(KERN_ALERT "smt went wrong!");
		return -1;
	}
	return -1;
}

int CreateDevice()
{
	MyClass = class_create(THIS_MODULE, CLASS_NAME);


	if(MyClass == NULL)
	{
		printk(KERN_ALERT "Couldn't initialize class");
		unregister_chrdev_region(dev, DEVICE_NAME);
		return -1;
	}

	if(device_create(MyClass, NULL, dev, NULL, DEVICE_NAME) == NULL) {
		printk("Couldn't init file!\n");
		unregister_chrdev_region(dev, DEVICE_NAME);
		return -1;
	}
	return 0;
}