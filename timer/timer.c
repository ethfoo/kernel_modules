#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

struct timer_list mytimer;
static void timer_handler(unsigned long data)
{
	mod_timer(&mytimer, jiffies + HZ);
	printk("current jiffies is %ld\n", jiffies);
}

static int __init mytimer_init(void)
{
	printk("mytimer init\n");

	init_timer(&mytimer);
	mytimer.expires = jiffies + HZ;
	mytimer.data = 0;
	mytimer.function = timer_handler;

	add_timer(&mytimer);

	return 0;

}

static void __exit mytimer_exit(void)
{
	printk("mytimer exit\n");
	del_timer_sync(&mytimer);
}

MODULE_LICENSE("GPL");

module_init(mytimer_init);
module_exit(mytimer_exit);
