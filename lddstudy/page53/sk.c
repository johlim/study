#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/slab.h>
#include <linux/vmalloc.h>

#include <asm/system_info.h>
#include <asm/delay.h>
#include <asm/io.h>
#include <linux/gpio.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include <linux/fs.h> // add
#include <linux/cdev.h> // add

#include <../arch/arm/mach-nxp4330/include/mach/platform.h> // from kernel/include
#include <../arch/arm/mach-nxp4330/include/mach/soc.h> // from kernel/include

static int onevalue = 1;
static char * twostring = NULL;
static int g_th_id = NULL;
module_param(onevalue, int, 0);
module_param(twostring, charp , 0);

static int sk_major=0, sk_minor=0;
static int result;
static dev_t sk_dev;
static struct file_operations sk_fops;
static struct cdev sk_cdev;

static int sk_register_cdev(void);

static int kthread_example_thr_fun(void *arg)
{
	printk(KERN_ALERT "@ %s() : called\n", __FUNCTION__);
	while(!kthread_should_stop())
	{
		//printk(KERN_ALERT "@ %s() : loop\n", __FUNCTION__);
		ssleep(1);
	}
	printk(KERN_ALERT "@ %s() : kthread_should_stop() called. Bye.\n", __FUNCTION__);
	return 0;
}

static void sk_threadinit(void)
{
	 
	  if(g_th_id == NULL){ 
		       g_th_id = (struct task_struct *)kthread_run(kthread_example_thr_fun, NULL, "kthread_example");
	  }
}
static int sk_init(void)
{

	printk(KERN_INFO "(%s)\n", __func__); 
	if ((result = sk_register_cdev()) < 0)
	{
		return result;	
	}

	return 0;
}


static void sk_exit(void)
{
	printk (KERN_INFO "good bye\n");
	cdev_del(&sk_cdev);
	unregister_chrdev_region(sk_dev, 1);
}

static int sk_register_cdev(void)
{
	int error;

	if (sk_major)
	{
		sk_dev = MKDEV(sk_major, sk_minor);
		error = register_chrdev_region(sk_dev,1,"sk");
	}
	else
	{
		error = alloc_chrdev_region(&sk_dev, sk_minor, 1, "sk");
		sk_major = MAJOR(sk_dev);
	}

	if (error < 0)
	{
		printk(KERN_WARNING "sk: cant get major %d\n", sk_major);
		return result;
	}
	
	printk("major number=%d\n", sk_major);

	cdev_init(&sk_cdev, &sk_fops);
	sk_cdev.owner = THIS_MODULE;
	sk_cdev.ops = &sk_fops;
	error = cdev_add(&sk_cdev, sk_dev, 1);

	if (error)
		printk(KERN_NOTICE"sk Register Error %d\n", error);
	return 0;
}

module_init(sk_init);
module_exit(sk_exit);

MODULE_LICENSE("Dual BSD/GPL");
//MODULE_LICENSE("Proprietary");
