obj-m += filter.o

KERNELDIR := /home/richard//ptxdist/linux-3.0/
PWD := $(shell pwd)


all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
