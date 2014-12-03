/*************************************************************************
	> File Name: key1.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Thu 06 Nov 2014 09:50:03 PM CST
 ************************************************************************/

/*
 *  * linux/drivers/char/mini210_buttons.c
 *   *
 *    * This program is free software; you can redistribute it and/or modify
 *     * it under the terms of the GNU General Public License version 2 as
 *      * published by the Free Software Foundation.
 *       */

 #include <linux/module.h>
 #include <linux/kernel.h>
 #include <linux/fs.h>
 #include <linux/init.h>
 #include <linux/delay.h>
 #include <linux/sched.h>
 #include <linux/poll.h>
 #include <linux/irq.h>
 #include <asm/irq.h>
 #include <asm/io.h>
 #include <linux/interrupt.h>
 #include <asm/uaccess.h>
 #include <mach/hardware.h>
 #include <linux/platform_device.h>
 #include <linux/cdev.h>
 #include <linux/miscdevice.h>

 #include <mach/map.h>
 #include <mach/gpio.h>
 #include <mach/regs-clock.h>
 #include <mach/regs-gpio.h>

 #define DEVICE_NAME"mybuttons"

 struct button_desc {
        int gpio;
        int number;
        char *name;
 };

 static struct button_desc buttons[] = {
        { S5PV210_GPH2(0), 0, "myKEY0"  },
 };

 static irqreturn_t button_interrupt(int irq, void *dev_id)
 {

        printk("<0> key down\n");

        return IRQ_HANDLED;

 }

 static int mini210_buttons_open(struct inode *inode, struct file *file)
 {
        int irq;
        int i;
        int err = 0;

     for (i = 0; i < ARRAY_SIZE(buttons); i++) {
                if (!buttons[i].gpio)
                    continue;

                irq = gpio_to_irq(buttons[i].gpio);
                err = request_irq(irq, button_interrupt, IRQ_TYPE_EDGE_BOTH, 
                                                buttons[i].name, (void *)&buttons[i]);
                if (err)
                    break;
            
     }

     if (err) {
                i--;
         for (; i >= 0; i--) {
                        if (!buttons[i].gpio)
                            continue;

                        irq = gpio_to_irq(buttons[i].gpio);
                        disable_irq(irq);
                        free_irq(irq, (void *)&buttons[i]);
         }

                return -EBUSY;
            
     }

        return 0;

 }
 

 static struct file_operations dev_fops = {
        .open= mini210_buttons_open,

 };

 static struct miscdevice misc = {
        .minor= MISC_DYNAMIC_MINOR,
        .name= DEVICE_NAME,
        .fops= &dev_fops,

 };

 static int __init button_dev_init(void)
 {
        int ret;

        ret = misc_register(&misc);

        return ret;

 }

 static void __exit button_dev_exit(void)
 {
        misc_deregister(&misc);

 }

 module_init(button_dev_init);
 module_exit(button_dev_exit);

 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("FriendlyARM Inc.");


