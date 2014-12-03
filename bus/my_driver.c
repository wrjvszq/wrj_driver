/*************************************************************************
	> File Name: my_driver.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Sat 08 Nov 2014 04:57:14 PM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/device.h>

MODULE_LICENSE("GPL");

extern struct bus_type my_bus_type;

int my_driver_probe(struct device *dev)
{
    printk("found the device and it had to use ");
    return 0;

}

struct device_driver my_driver = 
{
    .name = "my_dev",
    .bus = &my_bus_type,
    .probe = my_driver_probe,
};

static int my_driver_init(void)
{
    int ret = -1;
    
    ret = driver_register(&my_driver);

    return ret;
}

static void my_driver_exit(void)
{
    driver_unregister(&my_driver);
}

module_init(my_driver_init);
module_exit(my_driver_exit);
