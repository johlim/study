#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
static int onevalue = 1;
static char * twostring = NULL;

module_param(onevalue, int, 0);
module_param(twostring, charp , 0);

char * buf;
static int hello_init(void)
{
	if (onevalue && twostring)
	printk(KERN_INFO "Hello %d:%s \n", onevalue,twostring);
	else
	printk(KERN_INFO "Hello \n");


//	buf = kmalloc(1024, GFP_KERNEL);
	buf = kmalloc(1024, GFP_DMA);

	sprintf(buf, "myname is lim jong hoan");
	printk(KERN_INFO "kmalloc (%s)\n", buf); 

	return 0;
}


static void hello_exit(void)
{
	kfree(buf);
	printk(KERN_INFO "kfree \n"); 
	printk (KERN_INFO "good bye\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dal BSD/GPL");
//MODULE_LICENSE("Proprietary");
