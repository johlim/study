TARGET = client
#SOURCE = fork_main.c
SOURCE = client.c
CROSS_COMPILE=arm-linux-gnueabihf-
CC=$(CROSS_COMPILE)gcc
#LIB = -lpthread
#DEBUGOPTS = -fprofile-arcs -ftest-coverage -pg

all : $(TARGET)

$(TARGET):
	$(CC)	-o $(TARGET) $(SOURCE) -g $(DEBUGOPTS) $(LIB)
clean:
	rm $(TARGET)

