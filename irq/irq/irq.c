#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");

static int irq;
static char *interface;

module_param(interface, charp, 0644);
module_param(irq, int, 0644);


static irqreturn_t myirq_handler(int irq, void *dev)
{
	static int count = 0;
	if(count<10)
	{
		printk("handling the interrupt %d\n", irq);
		count++;
	}
	return IRQ_NONE;
}

static int myirq_init(void)
{
	printk("irq initing");
	if(request_irq(irq, &myirq_handler, IRQF_SHARED, interface, \
				&irq))
	{
		printk(KERN_ERR"cannot register %d\n", irq);
		return -EIO;
	}
	printk("%s on %d is register succeeded\n");
	return 0;
}

static void myirq_exit(void)
{
	printk("irq exiting\n");
	free_irq(irq, &irq);
	printk("%d freed\n", irq);
}


module_init(myirq_init);
module_exit(myirq_exit);
