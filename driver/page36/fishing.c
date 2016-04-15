#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello World 4.\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "GoodBye world 4.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("BSD");
MODULE_AUTHOR("limj@plk.co.kr");
MODULE_DESCRIPTION("Sample kernel driver ");
MODULE_SUPPORTED_DEVICE("minibuf");
