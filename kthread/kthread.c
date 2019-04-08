#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>

MODULE_DESCRIPTION("kthread test");
MODULE_AUTHOR("Stylon Wang <wangstylon@gmail.com>");
MODULE_LICENSE("GPL");

static struct kthread_worker *worker;

static void work_func(struct kthread_work *work)
{
  printk("%s work %p\n", __func__, work);
}

static int minit(void) 
{
  static struct kthread_work work;
  printk("kthread test init\n");

  worker = kthread_create_worker(0, "test worker");
  if (!worker)
  {
    printk("unable to create worker thread\n");
    return 1;
  }

  kthread_init_work(&work, work_func);

  {
  bool res = kthread_queue_work(worker, &work);
  printk("kthread_queue_work on work %p returned %d", &work, res);
  }

  return 0;
}

static void mexit(void)
{
  printk("kthread test exit\n");
  kthread_flush_worker(worker);
}

module_init(minit);
module_exit(mexit);
