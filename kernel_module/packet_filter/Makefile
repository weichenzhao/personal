target = filter
obj-m += filter.o
DEV_KERNELDIR := /lib/modules/$(shell uname -r)/build
KERNELDIR := /home/richard//ptxdist/linux-3.0/
PWD := $(shell pwd)


default:
	make -C $(KERNELDIR) M=$(PWD) modules

dev:
	make -C $(DEV_KERNELDIR) M=$(PWD) modules

install:
	sudo insmod $(target).ko

remove:
	sudo rmmod $(target)

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
