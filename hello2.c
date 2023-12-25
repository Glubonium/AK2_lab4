#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include "hello1.h"


MODULE_AUTHOR("Zahorodnii Vladyslav <vladzag2004@gmail.com>");
MODULE_DESCRIPTION("Hello 2, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint hello_counter = 1;
module_param(hello_counter, uint, 0444);
MODULE_PARM_DESC(hello_counter, "'Hello 2, world!' counter:");

static int __init hello2_init(void)
{
	pr_info("Hello 2, module entry.\n");
	print_hello(hello_counter);
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Hello 2, module exit.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
