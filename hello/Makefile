obj-m := hello.o

DIRS := /lib/modules/2.6.39/build/
all:
	make -C $(DIRS) M=$(PWD) modules
clean:
	rm -Rf *.o *.ko *.mod.c *.order *.symvers 
