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
u32 reg_rw_test_status;
u32 cpu_vers_no;
void nxp_cpu_vercheck(void)
{
	unsigned int rev, ver =0;

	rev = readl(__PB_IO_MAP_IROM_VIRT + 0x0100);
	switch(rev) {
		case 0xe153000a:	ver = 1; break;
		default:			ver = 0; break;
	}
	cpu_vers_no = ver;
	printk("CPU : VERSION = %u (0x%X)\n", cpu_vers_no, rev);
}


void nxp_nvs3320_rtccntread(void)
{
	unsigned int rev=0;

//	rev = readl(0xC0010C00 + 0x0004); fail
//	#define PHY_BASEADDR_RTC                        (0xC0010C00)
	u32 rtc = IO_ADDRESS(PHY_BASEADDR_RTC);
	rev = readl(rtc + 0x0004);
	printk("RTC : RTCCNTREAD =  %u\n", rev);
}

static int kthread_example_thr_fun(void *arg)
{
	printk(KERN_ALERT "@ %s() : called\n", __FUNCTION__);
	while(!kthread_should_stop())
	{
		//printk(KERN_ALERT "@ %s() : loop\n", __FUNCTION__);
		//nxp_cpu_vercheck();
		nxp_nvs3320_rtccntread();
		ssleep(1);
	}
	printk(KERN_ALERT "@ %s() : kthread_should_stop() called. Bye.\n", __FUNCTION__);
	return 0;
}

static void reg_rw_test_threadinit(void)
{
	 
	  if(g_th_id == NULL){ 
		       g_th_id = (struct task_struct *)kthread_run(kthread_example_thr_fun, NULL, "kthread_example");
	  }
}
static int reg_rw_test_init(void)
{

	reg_rw_test_threadinit();
	printk(KERN_INFO "(%s)\n", __func__); 

	return 0;
}


static void reg_rw_test_exit(void)
{
	printk (KERN_INFO "good bye\n");
	if(g_th_id){
		kthread_stop(g_th_id);
		g_th_id = NULL;
	}
}

module_init(reg_rw_test_init);
module_exit(reg_rw_test_exit);

MODULE_LICENSE("Dual BSD/GPL");
//MODULE_LICENSE("Proprietary");
