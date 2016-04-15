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

#include <linux/fs.h> 
#include <linux/cdev.h> 
#include <asm/uaccess.h> // add

#include <../arch/arm/mach-nxp4330/include/mach/platform.h> // from kernel/include
#include <../arch/arm/mach-nxp4330/include/mach/soc.h> // from kernel/include

#include "sk.h" // add

static int onevalue = 1;
static char * twostring = NULL;
module_param(onevalue, int, 0);
module_param(twostring, charp , 0);

static int sk_major=0, sk_minor=0;
static int result;
static dev_t sk_dev;
static struct cdev sk_cdev;

static int sk_register_cdev(void);
static int sk_open(struct inode * inode, struct file *filp);
static int sk_release(struct inode *inode, struct file *flip);
static int sk_write(struct file *filp, const char * buf, size_t count, loff_t * f_pos);
static int sk_read(struct file *filp, const char * buf, size_t count, loff_t * f_pos);
static int sk_ioctl(struct inode *inode, struct file *flip, unsigned int cmd, unsigned long arg);

static struct file_operations sk_fops = {
	.open = sk_open,
	.release = sk_release,
	.write = sk_write,
	.read = sk_read,
	.unlocked_ioctl = sk_ioctl,
};

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
static int sk_open(struct inode * inode, struct file *filp)
{
	printk("open\n");
	if (!try_module_get(THIS_MODULE)) return -ENODEV;
	filp->private_data = kmalloc(1024, GFP_KERNEL);
	sprintf(filp->private_data, "%d", onevalue);
	return 0;
}

static int sk_release(struct inode *inode, struct file *filp)
{
	printk("%s\n", filp->private_data);
	kfree(filp->private_data);
	printk("release\n");
	module_put(THIS_MODULE);
	return 0;
}
static int sk_write(struct file *filp, const char * buf, size_t count, loff_t * f_pos)
{
	copy_from_user((char *)filp->private_data, buf, count);
	return count;
}
static int sk_read(struct file *filp, const char * buf, size_t count, loff_t * f_pos)
{
	copy_to_user(buf, (char *)filp->private_data, count);
	return count;
}
static int sk_ioctl(struct inode *inode, struct file *flip, unsigned int cmd, unsigned long arg)
{
	printk("sk_ioctl (%x) (%x) \n", cmd, arg);

	if(_IOC_TYPE(cmd) != SK_MAGIC) return -EINVAL;
	if(_IOC_NR(cmd) >= SK_MAXNR ) return -EINVAL;
	switch(cmd)
	{
		case SK_0:
		case SK_1:
		case SK_2:
		case SK_3:
		case SK_4:
		case SK_5:
			printk("\n"); 
			printk("cmd %d\n", cmd); 
			printk("\n"); 
			break;
	}

	return 0;
}
module_init(sk_init);
module_exit(sk_exit);

MODULE_LICENSE("Dual BSD/GPL");
//MODULE_LICENSE("Proprietary");
