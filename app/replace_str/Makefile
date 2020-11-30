SYSROOT:=${SYSROOT}
CFLAGS= -g
CFLAGS:= ${CFLAGS} -O2
all : clean
	gcc hello_world.c -o hello_world ${CFLAGS} --sysroot=${SYSROOT}

clean :
	rm -f hello_world
