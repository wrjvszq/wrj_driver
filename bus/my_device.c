/*************************************************************************
	> File Name: my_device.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Sat 08 Nov 2014 05:24:01 PM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/device.h>

MODULE_LICENSE("GPL");

extern struct bus_type my_bus_type;

struct device my_device =
{
    .init_name = "my_dev",
    .bus = &my_bus_type,
};

static int my_device_init(void)
{
    device_register(&my_device);

    return 0;
}

static void my_device_exit(void)
{
    device_unregister(&my_device);
}

module_init(my_device_init);
module_exit(my_device_exit);
