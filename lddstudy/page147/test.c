#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/slab.h>
#include <linux/vmalloc.h>

static int onevalue = 1;
static char * twostring = NULL;

module_param(onevalue, int, 0);
module_param(twostring, charp , 0);

char * buf=NULL;
char * vbuf=NULL;
char * pbuf=NULL;
static int memtest_init(void)
{
	int order;

	if (onevalue && twostring)
	printk(KERN_INFO "MemTest %d:%s \n", onevalue,twostring);
	else
	printk(KERN_INFO "MemTest \n");


//	buf = kmalloc(1024, GFP_KERNEL);
	buf = kmalloc(1024, GFP_DMA);
	if (buf == NULL)
		return -1;
	// vmallc
	vbuf = vmalloc(1024*PAGE_SIZE);
	if (vbuf == NULL)
		return -1;
	// page
	order = get_order(1024 * 10);
	pbuf = __get_free_pages(GFP_KERNEL, order);
	if (pbuf == NULL)
		return -1;
	free_pages(pbuf, order);

	sprintf(buf, "myname is lim jong hoan");
	printk(KERN_INFO "kmalloc (%s)\n", buf); 

	return 0;
}


static void memtest_exit(void)
{
	if (vbuf)
	{
	vfree(vbuf);
	printk(KERN_INFO "vfree \n"); 
	}
	if (buf)
	{
	kfree(buf);
	printk(KERN_INFO "kfree \n"); 
	}
	printk (KERN_INFO "good bye\n");
}

module_init(memtest_init);
module_exit(memtest_exit);

MODULE_LICENSE("Dal BSD/GPL");
//MODULE_LICENSE("Proprietary");
