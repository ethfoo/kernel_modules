#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>


static struct tasklet_struct mytasklet;

static void tasklet_handler(unsigned long data)
{
	printk("doing my tasklet_handler\n");
}

static int __init mytasklet_init(void)
{
	printk("mytasklet started..\n");
	tasklet_init(&mytasklet, tasklet_handler, 0);
	tasklet_schedule(&mytasklet);
	return 0;
}

static void __exit mytasklet_exit(void)
{
	tasklet_kill(&mytasklet);
	printk("mytasklet exited..\n");
}

MODULE_LICENSE("GPL");

module_init(mytasklet_init);
module_exit(mytasklet_exit);
