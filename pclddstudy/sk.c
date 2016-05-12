#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#define RDWR_DEV_NAME	"rdwrdev"
#define RDWR_DEV_MAJOR	(240)
#define RDWR_WRITE_ADDR	0x378
#define RDWR_READ_ADDR 	0x379

static int allow_live_bait = 1;
module_param(allow_live_bait, bool, 0644);
int rdwr_open(struct inode * inode, struct file * filp)
{
	printk(KERN_ERR "rdwr_open\n");
	return 0;
}

int rdwr_release(struct inode * inode, struct file * filp)
{
	printk(KERN_ERR "rdwr_release\n");
	return 0;
}

int rdwr_read(struct file *filp,  char * buf, size_t count, loff_t * f_pos)
{
	int loop;
	unsigned char status;
	printk(KERN_ERR "rdwr_read\n");
	for(loop =0; loop < count; loop++)
	{
		status = inb(RDWR_READ_ADDR);
		put_user(status, (char *)&buf[loop]);
	}

	return count;
}
struct file_operations rdwr_fops = {
	.owner = THIS_MODULE,
	.open	= rdwr_open,
	.release	= rdwr_release,
	.read	= rdwr_read,
};


static int param_init(void)
{
	int result;

	printk("init : %d \n",allow_live_bait );
	
	result = register_chrdev(RDWR_DEV_MAJOR, RDWR_DEV_NAME, &rdwr_fops);

	if (result < 0) return result;
	return 0;
}

static void param_exit(void)
{
	printk("exit : %d \n",allow_live_bait );
	
	unregister_chrdev(RDWR_DEV_MAJOR, RDWR_DEV_NAME);
}

int get_my_status(void)
{
	return allow_live_bait;
}

EXPORT_SYMBOL_GPL(get_my_status);

module_init(param_init);
module_exit(param_exit);
MODULE_LICENSE("Dual BSD/GPL");


