obj-m := memdev.o
KDIR := /home/wrj/my_linux/kernel_module/linux-smart210 
all :
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-
clean :
	rm -rf *.o *.order *.ko *.mod.o *.mod.c *.symvers
