#include<linux/init.h>
#include<linux/module.h>

static int hello_init(void)
{
	printk("<0> hello\n");
	return 0;
}

static void hello_exit(void)
{

}

	module_init(hello_init);
	module_exit(hello_exit);
