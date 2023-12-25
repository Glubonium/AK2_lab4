#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"


MODULE_AUTHOR("Zahorodnii Vladyslav <vladzag2004@gmail.com>");
MODULE_DESCRIPTION("Hello 1, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct event_data {
	struct list_head list_node;
	ktime_t timestamp;
	ktime_t print_duration;
};

static LIST_HEAD(head_node);

void print_hello(uint hello_counter)
{
	int i;
	if (hello_counter == 0) {
		pr_warn("Parameter is 0.\n");
	} else if ((hello_counter >= 5) && (hello_counter <= 10)) {
		pr_warn("Parameter is between 5 and 10.\n");
	} else if (hello_counter > 10) {
		pr_err("Parameter is larger than 10.\n");
		return -EINVAL;
	}

	for (i = 0; i < hello_counter; i++) {
		struct event_data *event = NULL;
		event = kmalloc(sizeof(*event), GFP_KERNEL);
		event->timestamp = ktime_get();
		pr_info("Hello 1, world!\n");

		event->print_duration = ktime_sub(ktime_get(), event->timestamp);
		list_add(&event->list_node, &head_node);
	}
	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("Hello 1, module entry.\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct event_data *event, *tmp;
	list_for_each_entry_safe(event, tmp, &head_node, list_node) {
		ktime_t duration = ktime_sub(ktime_get(), event->timestamp);
		pr_info("Event time: %lld ns\n", ktime_to_ns(duration), ktime_to_ns(event->print_duration));
		list_del(&event->list_node);
		kfree(event);
	}
	pr_info("Hello 1, module exit.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
