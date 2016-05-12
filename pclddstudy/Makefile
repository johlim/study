obj-m := sk.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)
default : 
#	make -C /home/limjh/kernel SUBDIRS=`pwd` modules
#	make -C /home/limjh/pckernel/kernel SUBDIRS=`pwd` modules
#	make -C /lib/modules/3.2.0-82-generic-pae/build M=`pwd` modules
	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(PWD) modules

clean :
	rm *.o
	rm *.ko
	rm *.mod.c
	rm modules.order
	rm Module.symvers
