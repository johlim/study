CC=gcc
CFLAGS=-I.
DEPS=t.h
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CLFAGS)
hellomake: t.o
	gcc -o hellomake t.o  -I.

clean :
	rm hellomake
