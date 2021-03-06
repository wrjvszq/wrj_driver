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
#include<linux/input.h>

MODULE_LICENSE("GPL");

struct work_struct work1;
struct timer_list key_timer;
unsigned int key_value = 0;
wait_queue_head_t key_q;
struct input_dev *button_dev = NULL;

void work1_func(struct work_struct *work)
{
    mod_timer(&key_timer,jiffies + (HZ/10));
}

void key_timer_func(void)
{
    if(!(gpio_get_value(S5PV210_GPH2(0))))
    {
        key_value = 1;
        input_report_key(button_dev,KEY_1,1);

    }
    
    if(!(gpio_get_value(S5PV210_GPH3(3))))
    {
        key_value = 8;
        input_report_key(button_dev,KEY_8,1);
    }

    input_sync(button_dev);
}

irqreturn_t key_irq(int irq, void * key_id)
{
    //1 check whether the key irq produce

    //2 clean the key irq

    //3 printf the key value

    schedule_work(&work1);
}


static int my_key_init(void)
{
    button_dev = input_allocate_device();
    set_bit(EV_KEY,button_dev->evbit);

    set_bit(KEY_1,button_dev->keybit);
    set_bit(KEY_8,button_dev->keybit);

    input_register_device(button_dev);

    request_irq(gpio_to_irq(S5PV210_GPH2(0)),key_irq,IRQF_TRIGGER_FALLING,"key",0);//creat
    request_irq(gpio_to_irq(S5PV210_GPH3(3)),key_irq,IRQF_TRIGGER_FALLING,"key",1);//creat

    INIT_WORK(&work1,work1_func);
    init_timer(&key_timer);
    key_timer.function = key_timer_func;

    add_timer(&key_timer);

    return 0;
}

static void my_key_exit(void)
{
    input_unregister_device(button_dev);
    free_irq(gpio_to_irq(S5PV210_GPH2(0)),0);
    free_irq(gpio_to_irq(S5PV210_GPH3(3)),1);
}


module_init(my_key_init);
module_exit(my_key_exit);
