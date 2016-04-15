obj-m += fishing.o

KDIR:=/home/jhlim/kernel
CC=$(CROSSNAME)gcc
PWD=`pwd`

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
