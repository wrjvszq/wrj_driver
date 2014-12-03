obj-m := memdev.o
KDIR := /home/wrj/my_linux/kernel_module/linux-smart210/  
all :
		make -C $(KDIR) M=$(PWD) modules CROSS_COMPIOLE=arm-linux- ARCH=arm
clean :
	rm -rf *.o *.order *.ko *.mod.o *.mod.c *.symvers
