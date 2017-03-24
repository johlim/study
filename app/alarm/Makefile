CROSSNAME=arm-cortex_a9-linux-gnueabi-
TARGET = alarm_test
SOURCE = alarm_main.c
CC=$(CROSSNAME)gcc
CC=gcc
LIB = -lpthread
DEBUGOPTS = #-fprofile-arcs -ftest-coverage -pg

all : $(TARGET) $(SOURCE)

$(TARGET):
	$(CC)	-o $(TARGET) $(SOURCE) -g $(DEBUGOPTS) $(LIB)

clean :
	rm $(TARGET)

