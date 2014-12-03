/*************************************************************************
	> File Name: my_bus.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Sat 08 Nov 2014 04:30:22 PM CST
 ************************************************************************/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>

MODULE_LICENSE("GPL");

static int my_bus_match(struct device * dev,struct device_driver * drv)
{
    return !strncmp(dev ->kobj.name,drv ->name,strlen(drv ->name));
}

struct bus_type my_bus_type =
{
    .name = "my_bus",
    .match = my_bus_match,

};

EXPORT_SYMBOL(my_bus_type);
static int my_bus_init(void)
{
    int ret = -1;

    ret = bus_register(&my_bus_type);

    return ret;
}

static void my_bus_exit(void)
{
    bus_unregister(&my_bus_type);

}

module_init(my_bus_init);
module_exit(my_bus_exit);
