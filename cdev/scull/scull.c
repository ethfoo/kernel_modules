#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>


static int scull_major = 0, scull_minor;
module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);

static int scull_nr_devs = 4;	//次设备个数
static dev_t dev_num;	//声明设备号

struct scull_dev {
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned long size;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
} dev;



ssize_t scull_open(struct inode *inode, struct file *filp)
{
	/*获得dev的地址，并存入到filp的私有data中*/
	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev;

	if( (filp->f_flags & O_ACCMODE) == O_WRONLY ) {
	//	scull_trim(dev);
	}
	return 0;
}

int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}

ssize_t scull_read(struct file *filp, char __user *buff, size_t count, loff_t *ppos)
{

	return 0;
}

ssize_t scull_write(struct file *filp, char __user *buff, size_t count, loff_t *ppos)
{
	return 0;
}

struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.read = scull_read,
	.write = scull_write,
	.open = scull_open,
	.release = scull_release,
};

static void scull_alloc_nums(void)
{
	/*分配设备编号
	 *一般使用动态分配,但保留加载时指定主设备号的余地
	 */
	
	int result;
	/*主设备号默认为0，如果用户指定设备号，scull_major不为0，使用静态分配*/
	if(scull_major){
		dev_num = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev_num, scull_nr_devs, "scull");

	}
	/*动态分配*/
	else{
		result = alloc_chrdev_region(&dev_num, 0, scull_nr_devs, "scull");
		scull_major = MAJOR(dev_num);
		printk("the dynamic allocation of major num is %d\n", scull_major);
	}

	if(result){
		printk(KERN_WARNING "scull:can't get major %d\n", scull_major);
		return result;
	}

}

static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err;
	int devno = MKDEV(scull_major, scull_minor+index);
	
	/*初始化struct cdev*/
	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;

	/*添加struct cdev*/
	err = cdev_add(&dev->cdev, devno, 1);
	if(err) {
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
	}
}

static int __init scull_init(void)
{
	printk("scull init..\n");

	/*分配设备编号*/
	scull_alloc_nums();

	/*注册字符设备*/
	scull_setup_cdev(&dev, 0);

	return 0;
}

static void __exit scull_exit(void)
{
	printk("scull exit..\n");

	/*释放设备编号*/
	unregister_chrdev_region(dev_num, scull_nr_devs);

	/*移除字符设备*/
	cdev_del(&dev);


}

MODULE_LICENSE("GPL");

module_init(scull_init);
module_exit(scull_exit);
