/*************************************************************************
	> File Name: led.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Wed 29 Oct 2014 07:23:53 PM CST
 ************************************************************************/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/io.h>

#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>

#include "led.h"

#define GPC0CON 0xe0200280
#define GPC0DAT 0xe0200284

struct cdev led_dev;
dev_t led_no;

unsigned int * led_ctl;
unsigned int * led_data;

int led_open(struct inode *node, struct file *filp)
{
    led_ctl = ioremap(GPC0CON,4);
    writel(0x1111,led_ctl);   

    led_data = ioremap(GPC0DAT,4);

    return 0;
}

long led_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch(cmd)
    {
       case LED_ON:
           writel(0x0,led_data);
           return 0;
       case LED_OFF:
           writel(0xffff,led_data);
           return 0;
        default:
           return -EINVAL;
    }
}

static const struct file_operations led_fops =
{
    .open = led_open,
    .unlocked_ioctl = led_ioctl,
};

static int led_init(void)
{
    cdev_init(&led_dev,&led_fops);
    alloc_chrdev_region(&led_no,0,1,"myled");

    cdev_add(&led_dev,led_no,1);

    return 0;
}

static void led_exit(void)
{
    cdev_del(&led_dev);
    unregister_chrdev_region(&led_no,1);

}

module_init(led_init);
module_exit(led_exit);
