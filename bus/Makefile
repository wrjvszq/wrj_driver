obj-m := my_bus.o my_driver.o my_device.o
KDIR := /home/wrj/my_linux/kernel_module/linux-smart210 
all:
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-
clean:
	rm *.ko  *.mod.c *.o *.order *.symvers

