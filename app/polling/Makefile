CROSSNAME=arm-cortex_a9-linux-gnueabi-
TARGET = test_poll
OBJECTS = poll_main.o
SOURCES = poll_main.c
CC=$(CROSSNAME)gcc
CC=gcc
LIB = -lpthread
DEBUGOPTS = #-fprofile-arcs -ftest-coverage -pg

all : clean build $(TARGET)

$(TARGET):
	$(CC)	-o $(TARGET) $(OBJECTS) -g $(DEBUGOPTS) $(LIB)

build: 
	$(CC)	-c $(SOURCES) -g $(DEBUGOPTS) $(LIB)

clean :
	rm -f $(TARGET) *.o

