#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int myint;
static char * mystring="12";
static int myintArray[2]={0,1};
static int arr_argc = 2;

module_param(myint, int, S_IWUSR);
MODULE_PARM_DESC(myint, "integer");

module_param(mystring, charp, S_IWUSR);
MODULE_PARM_DESC(mystring, "char * ");

module_param_array(myintArray, int, &arr_argc, S_IWUSR);
MODULE_PARM_DESC(myintArray, "int array count 2");

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello World 5.\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "GoodBye world 5.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("BSD");
MODULE_AUTHOR("limj@plk.co.kr");
MODULE_DESCRIPTION("Sample kernel driver ");
MODULE_SUPPORTED_DEVICE("minibuf");
