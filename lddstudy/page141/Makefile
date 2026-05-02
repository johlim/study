obj-m 	+= test.o
module-objs := test1.o test2.o test3.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
		$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
		$(MAKE) -C $(KDIR) M=$(PWD) clean
		rm -rf *.ko *.o .*.cmd Module.symvers modules.order
