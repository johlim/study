OBJECTS = glib_test.o 
TARGET = a.out
LINKFLAG = -shared -Wl,-soname,libtest.so.1 -o libtest.so.1.0.1 ./main.o
LNCMD = ln -s libtest.so.1.0.1 libtest.so.1 ; ln -s libtest.so.1.0.1 libtest.so
CFLAGS = -g2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lglib-2.0 
all: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)  $(CFLAGS)

lib: main.o
	$(CC) $(CFLAGS) -c $<
	$(CC) $(LINKFLAG)
#	$(LNCMD)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)
