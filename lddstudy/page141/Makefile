obj-m 	+= test.o
module-objs := test1.o test2.o test3.o

default :
#	make -C /home/jhlim/kernel  M=`pwd`
	make -C /home/jhlim/kernel  SUBDIRS=`pwd`

clean :
	rm -rf *.ko
	rm *.o
	rm .*.cmd
