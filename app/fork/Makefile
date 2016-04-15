TARGET = fork_test
#SOURCE = fork_main.c
SOURCE = fork_share.c
CC=$(CROSSNAME)gcc
LIB = -lpthread
DEBUGOPTS = -fprofile-arcs -ftest-coverage -pg

all : $(TARGET)

$(TARGET):
	$(CC)	-o $(TARGET) $(SOURCE) -g $(DEBUGOPTS) $(LIB)

clean :
	rm *.gcno
	rm $(TARGET)

