/*混杂设备驱动模板
  可用于试验内核
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>

#define DEVICE_NAME "dev_test"



static ssize_t demo_read(struct file *file, char _user *buf, size_t count, loff_t *ppos)
{
	ssize_t result = 0;

	return result;
}

static ssize_t demo_write(struct file *file, const char _user *buf, size_t count, loff_t *ppos)
{
	ssize_t result = 0;

	return result;
}

static struct file_operations dev_fops =
{
	.owner = THIS_MODULE,
	.read = demo_read,
	.write = demo_write
};


static struct miscdevice misc = 
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops
};

static int _init demo_init(void)
{
	//建立设备文件
	int ret = misc_register(&misc);

	return ret;
}

static void _exit demo_exit(void)
{
	misc_deregister(&misc);
}


module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");


















