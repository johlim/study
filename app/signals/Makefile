TARGET = signal_test
#SOURCE = blocksignal.c 
#SOURCE = blocksigusr.c 
#SOURCE = pibonacci.c
SOURCE = signal_ctrl.c
#CC=$(CROSSNAME)gcc
LIB = -lpthread
DEBUGOPTS = -fprofile-arcs -ftest-coverage -pg

all : $(TARGET)

$(TARGET):
	$(CC)	-o $(TARGET) $(SOURCE) -g $(DEBUGOPTS) $(LIB)

clean :
	rm *.gcno
	rm $(TARGET)

