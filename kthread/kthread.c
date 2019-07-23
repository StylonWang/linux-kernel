#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>

MODULE_DESCRIPTION("kthread test");
MODULE_AUTHOR("Stylon Wang <wangstylon@gmail.com>");
MODULE_LICENSE("GPL");

int do_timer_crash = 0;
MODULE_PARM_DESC(timer_crash, "Deliberately crash in a timer (1 = enable)");
module_param_named(timer_crash, do_timer_crash, int, 0444);

static struct kthread_worker *worker;

static void timer_handler(struct timer_list *t)
{
  printk("%s timer %p do crash %d\n", __func__, t, do_timer_crash);
  if (do_timer_crash) {
    char* invalid_ptr = (char *)0x3;
    *invalid_ptr = 'c';
  }
}

DEFINE_TIMER(crash_timer, timer_handler);

static void work_func(struct kthread_work *work)
{
  printk("%s work %p\n", __func__, work);
  mod_timer(&crash_timer, jiffies + HZ);
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
  kthread_destroy_worker(worker);
}

module_init(minit);
module_exit(mexit);
