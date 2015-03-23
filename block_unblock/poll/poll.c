#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/poll.h>

#define DEVICE_NAME "poll_select"
#define MAX_BUFFER_SIZE 20

static char buffer[MAX_BUFFER_SIZE];
static int buffer_char_count = 0;
static wait_queue_head_t my_queue;
struct semaphore sem;

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

	init_waitqueue_head(&my_queue);
	sema_init(&sema, 1);

	printk("demo init success!\n");
	return ret;
}

static void _exit demo_exit(void)
{
	misc_deregister(&misc);
	printk("demo exit success!\n");
}


module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");


















