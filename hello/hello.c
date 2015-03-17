#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

static int hello_init(void)
{
	printk("<0>hello, kernel\n");
	return 0;
}

static void hello_exit(void)
{
	printk("<0>goodbye, kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);

