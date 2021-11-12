TARGET = hello_world

SOURCE = hello_main.c hello_table.c hello_time.c
CC=$(CROSS_COMPILE)gcc
LIB = -lpthread
#DEBUGOPTS = -fprofile-arcs -ftest-coverage -pg
DEBUGOPTS = -g

all : clean $(TARGET)

$(TARGET):
	$(CC)	-o $(TARGET) $(SOURCE) $(DEBUGOPTS) $(LIB)

clean :
	rm -f $(TARGET)
	rm -f *.o
	rm -f *.gcno

