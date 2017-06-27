TARGET = mesg_test
#SOURCE = fork_main.c
SOURCE = main.c pd_message.c
#CC=$(CROSSNAME)gcc
CC=gcc
LIB = -lpthread
DEBUGOPTS = -fprofile-arcs -ftest-coverage -pg
DEBUGOPTS = 

all : $(TARGET)

$(TARGET):
	        $(CC)   -o $(TARGET) $(SOURCE) -g $(DEBUGOPTS) $(LIB)

clean :
			rm $(TARGET)

