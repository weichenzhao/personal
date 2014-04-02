target = chardev
obj-m += chardev.o
DEV_KERNELDIR := /lib/modules/$(shell uname -r)/build
KERNELDIR := /home/richard//ptxdist/linux-3.0/
PWD := $(shell pwd)


default:
	make -C $(KERNELDIR) M=$(PWD) modules
	gcc -c -fPIC read_one_pkt.c
	gcc -shared read_one_pkt.o -o read_one_pkt.so

dev:
	make -C $(DEV_KERNELDIR) M=$(PWD) modules

install:
	sudo insmod $(target).ko

remove:
	sudo rmmod $(target)

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	rm *.so
