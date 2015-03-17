#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

static int __init mytimer_init(void)
{
	unsigned long total_sec;
	int hours, minutes, seconds;

	printk("my timer init\n");
	total_sec = jiffies/HZ;
	printk("the time to now is %ld\n", total_sec);

	hours = total_sec/(60*60);
	minutes = (total_sec%(60*60))/60;
	seconds = (total_sec%(60*60))%60;

	printk("hours:%d, minutes:%d, seconds:%d\n", hours, minutes, seconds);
	
	return 0;

}

static void __exit mytimer_exit(void)
{
	printk("mytimer exit\n");
}

MODULE_LICENSE("GPL");

module_init(mytimer_init);
module_exit(mytimer_exit);
