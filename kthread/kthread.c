#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("kthread test");
MODULE_AUTHOR("Stylon Wang <wangstylon@gmail.com>");
MODULE_LICENSE("GPL");

static int minit(void) 
{
  printk("kthread test init\n");
  return 0;
}

static void mexit(void)
{
  printk("kthread test exit\n");
}

module_init(minit);
module_exit(mexit);
