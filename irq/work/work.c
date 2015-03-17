#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>

static struct work_struct mywork;

static void work_handler(void *data)
{
	printk("mywork_handler is working");
}

static int mywork_init(void)
{
	printk("mywork is starting\n");
	INIT_WORK(&mywork, work_handler);
	schedule_work(&mywork);
	return 0;
}

static void mywork_exit(void)
{
	printk("mywork is exiting\n");	
}

MODULE_LICENSE("GPL");

module_init(mywork_init);
module_exit(mywork_exit);
