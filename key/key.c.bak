/*************************************************************************
	> File Name: key.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Thu 30 Oct 2014 05:58:28 PM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/miscdevice.h>
#include<linux/fs.h>
#include<linux/interrupt.h>
#include<linux/io.h>
#include<linux/irq.h>
#include<mach/gpio.h>
#include<asm/uaccess.h>
#include<linux/sched.h>

MODULE_LICENSE("GPL");

struct work_struct work1;
struct timer_list key_timer;
unsigned int key_value = 0;
wait_queue_head_t key_q;

void work1_func(struct work_struct *work)
{
    mod_timer(&key_timer,jiffies + (HZ/10));
}

void key_timer_func(void)
{
    if(!(gpio_get_value(S5PV210_GPH2(0))))
    {
        key_value = 1;
    }
    
    if(!(gpio_get_value(S5PV210_GPH3(3))))
    {
        key_value = 8;
    }

    wake_up(&key_q);
}

irqreturn_t key_irq(int irq, void * key_id)
{
    //1 check whether the key irq produce

    //2 clean the key irq

    //3 printf the key value

    schedule_work(&work1);
}

int key_open(struct inode * inode,struct file *file)
{
    return 0;
}

ssize_t key_read(struct file *filp, char __user *buf, size_t size, loff_t *pos)
{
    wait_event(key_q,key_value);

    printk("<0> kerenl        %d      \n",key_value);
    copy_to_user(buf,&key_value,4);

    key_value = 0;

    return 4;
}

static const struct file_operations key_fops =
{
    .open = key_open,
    .read = key_read,
};

static struct miscdevice key_dev =
{
    .minor = 233,
    .name = "key",
    .fops = &key_fops,
};

static int my_key_init(void)
{
    int ret;
    ret = misc_register(&key_dev);
    if(ret != 0)
    {
        printk("fail! ");
    }
    
    request_irq(gpio_to_irq(S5PV210_GPH2(0)),key_irq,IRQF_TRIGGER_FALLING,"key",0);//creat
    request_irq(gpio_to_irq(S5PV210_GPH3(3)),key_irq,IRQF_TRIGGER_FALLING,"key",1);//creat

    INIT_WORK(&work1,work1_func);
    init_timer(&key_timer);
    key_timer.function = key_timer_func;

    add_timer(&key_timer);
    init_waitqueue_head(&key_q);


    return 0;
}

static void my_key_exit(void)
{
    misc_deregister(&key_dev);
    free_irq(gpio_to_irq(S5PV210_GPH2(0)),0);
    free_irq(gpio_to_irq(S5PV210_GPH3(3)),1);
}


module_init(my_key_init);
module_exit(my_key_exit);
