#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
static int onevalue = 1;
static char * twostring = NULL;

module_param(onevalue, int, 0);
module_param(twostring, charp , 0);

static int hello_init(void)
{
	if (onevalue && twostring)
	printk("Hello %d:%s \n", onevalue,twostring);
	else
	printk("Hello \n");
	return 0;
}


static void hello_exit(void)
{
	printk (KERN_INFO "good bye\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dal BSD/GPL");
//MODULE_LICENSE("Proprietary");
