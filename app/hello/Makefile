TARGET = hello_world

SOURCE = hello_main.c hello_table.c
CC=$(CROSS_COMPILE)gcc
LIB = -lpthread
#DEBUGOPTS = -fprofile-arcs -ftest-coverage -pg

all : clean $(TARGET)

$(TARGET):
	$(CC)	-o $(TARGET) $(SOURCE) -g $(DEBUGOPTS) $(LIB)

clean :
	rm -f $(TARGET)
	rm -f *.o
	rm -f *.gcno

