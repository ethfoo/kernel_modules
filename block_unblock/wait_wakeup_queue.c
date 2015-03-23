#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>

#define KPRT(msg) printk("msg\n");

#define DEVICE_NAME "dev_test"
#define MAX_BUFFER_SIZE 20

static char kernel_buffer[MAX_BUFFER_SIZE];
static int buffer_char_count = 0;
static wait_queue_head_t my_queue;



static ssize_t demo_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	ssize_t result = 0;

	if(buffer_char_count == 0)
	{
		wait_event_interruptible(my_queue, buffer_char_count);
	}
	else
	{
		if(copy_to_user(buf, kernel_buffer, count))
			return -EINVAL;

		buffer_char_count = 0;
	}
	result = count;

	return result;
}

static ssize_t demo_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	ssize_t result = 0;

	if(buffer_char_count == 0)
	{
		if(copy_from_user(kernel_buffer, buf, count))
			return -EINVAL;

		result = count;
		buffer_char_count = result;

		wake_up_interruptible(&my_queue);
	}

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

static int __init demo_init(void)
{
	//建立设备文件
	int ret = misc_register(&misc);
	KPRT(dev_test register success);

	//初始化等待队列头
	init_waitqueue_head(&my_queue);

	return ret;
}

static void __exit demo_exit(void)
{
	misc_deregister(&misc);
	KPRT(dev_test exit success);
}


module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");



