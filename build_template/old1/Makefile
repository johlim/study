CC	= @CC@
CFLAGS	= @CFLAGS@
LDFLAGS	= @LIBS@

all : a.out

a.out : alarm_main.c
	$(CC) $(CFALGS) -o $@ $^ $(LDFLAGS)

clean :
	@rm -rf *.o $@
