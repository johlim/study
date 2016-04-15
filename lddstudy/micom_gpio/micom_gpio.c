#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/slab.h>
#include <linux/vmalloc.h>

#include <asm/system_info.h>
#include <asm/delay.h>
#include <linux/gpio.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include <../arch/arm/mach-nxp4330/include/mach/platform.h> // from kernel/include
#include <../arch/arm/mach-nxp4330/include/mach/soc.h> // from kernel/include

static int onevalue = 1;
static char * twostring = NULL;

module_param(onevalue, int, 0);
module_param(twostring, charp , 0);

char * buf=NULL;
char * vbuf=NULL;
char * pbuf=NULL;
struct task_struct *g_th_id=NULL;
u32 gpiotest_status;

#define CFG_IO_MICOM_RESERVE0				((PAD_GPIO_E + 20) | PAD_FUNC_ALT0)		/* GPIO */
#define CFG_IO_MICOM_WD							((PAD_GPIO_E + 21) | PAD_FUNC_ALT0)		/* GPIO */
#define CFG_IO_MICOM_RESERVE1				((PAD_GPIO_E + 23) | PAD_FUNC_ALT0)		/* GPIO */

#define CFG_IO_LED_FRONT0				((PAD_GPIO_B + 27))		/* GPIO */
#define CFG_IO_LED_REAR1				((PAD_GPIO_B + 28))		/* GPIO */
#define CFG_IO_LED_REAR2				((PAD_GPIO_B + 29))		/* GPIO */

static void gpio_swing(void)
{
	gpio_request(CFG_IO_LED_REAR2, "hi");

	gpio_direction_output(CFG_IO_LED_REAR2, 1);

	if (gpiotest_status)
		gpio_set_value(CFG_IO_LED_REAR2,0);
	else
		gpio_set_value(CFG_IO_LED_REAR2,1);

	gpio_free(CFG_IO_LED_REAR2);
}

static void nx_gpio_swing(void)
{

	nxp_soc_gpio_set_out_value(CFG_IO_LED_FRONT0, 0);
	nxp_soc_gpio_set_io_dir(CFG_IO_LED_FRONT0, 1);
	nxp_soc_gpio_set_io_func(CFG_IO_LED_FRONT0,
			nxp_soc_gpio_get_altnum(CFG_IO_LED_FRONT0));

	if (gpiotest_status)
		nxp_soc_gpio_set_out_value(CFG_IO_LED_FRONT0, 1);
	else
		nxp_soc_gpio_set_out_value(CFG_IO_LED_FRONT0, 0);


}

static void gpio2_swing(void)
{
	gpio_request(CFG_IO_LED_REAR1, "LED_REAR1");

	gpio_direction_output(CFG_IO_LED_REAR1, 1);

	if (gpiotest_status)
		gpio_set_value(CFG_IO_LED_REAR1,1);
	else
		gpio_set_value(CFG_IO_LED_REAR1,0);

	gpio_free(CFG_IO_LED_REAR1);
}


static int kthread_example_thr_fun(void *arg)
{
	printk(KERN_ALERT "@ %s() : called\n", __FUNCTION__);
	gpiotest_status=0;
	while(!kthread_should_stop())
	{
		//printk(KERN_ALERT "@ %s() : loop\n", __FUNCTION__);
		gpiotest_status = ~gpiotest_status;
		nx_gpio_swing();
		gpio_swing();
		gpio2_swing();
		ssleep(1);
	}
	printk(KERN_ALERT "@ %s() : kthread_should_stop() called. Bye.\n", __FUNCTION__);
	return 0;
}

static void gpiotest_threadinit(void)
{
	 
	  if(g_th_id == NULL){ 
		       g_th_id = (struct task_struct *)kthread_run(kthread_example_thr_fun, NULL, "kthread_example");
	  }
}
static int gpiotest_init(void)
{

	gpiotest_threadinit();
	printk(KERN_INFO "(%s)\n", __func__); 

	return 0;
}


static void gpiotest_exit(void)
{
	printk (KERN_INFO "good bye\n");
	if(g_th_id){
		kthread_stop(g_th_id);
		g_th_id = NULL;
	}
}

module_init(gpiotest_init);
module_exit(gpiotest_exit);

MODULE_LICENSE("Dual BSD/GPL");
//MODULE_LICENSE("Proprietary");
