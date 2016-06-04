OBJECTS = test.o libtest.so.1.0.1
TARGET = a.out
LINKFLAG = -shared -Wl,-soname,libtest.so.1 -o libtest.so.1.0.1 ./main.o
LNCMD = ln -s libtest.so.1.0.1 libtest.so.1 ; ln -s libtest.so.1.0.1 libtest.so
CFLAGS = -g2 
all: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) -L./ -I./ -ltest

lib: main.o
	$(CC) $(CFLAGS) -c $<
	$(CC) $(LINKFLAG)
#	$(LNCMD)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)
