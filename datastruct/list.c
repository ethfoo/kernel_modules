#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>

struct student{
	char *name;
	int age;
	struct list_head list;
};

static int list_init(void)
{
	printk("list_init\n");

	struct list_head head;
	INIT_LIST_HEAD(&head); 

	struct student stu1 = {
		.name = "Felix",
		.age = 23
	};

	struct student stu2 = {
		.name = "ethan",
		.age = 24
	};

	list_add(&stu1.list, &head);
	list_add(&stu2.list, &stu1.list);

	struct list_head *pos = NULL;
	struct student *pstu = NULL;
	list_for_each(pos, &head)
	{
		pstu = list_entry(pos, struct student, list);
		printk("stduent.name=%s, student.age=%d\n", pstu->name, pstu->age);
	}

	return 0;
}

static void list_exit(void)
{
	printk("list_exit\n");
}

MODULE_LICENSE("GPL"); 

module_init(list_init);
module_exit(list_exit);
