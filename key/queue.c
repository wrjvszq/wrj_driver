/*************************************************************************
	> File Name: queue.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Thu 06 Nov 2014 08:12:22 PM CST
 ************************************************************************/

#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

static struct workqueue_struct *my_work;
static struct work_struct work1;
static struct work_struct work2;

static void work1_func(void)
{
    printk("this is work 1\n");
}

static void work2_func(void)
{
    printk("this is work 2\n");
}

static int queue_init(void)
{
    INIT_WORK(&work1,work1_func);

    schedule_work(&work1);

    INIT_WORK(&work2,work2_func);

    schedule_work(&work2);

    return 0;
}

static void queue_exit(void)
{

}

module_init(queue_init);
module_exit(queue_exit);
