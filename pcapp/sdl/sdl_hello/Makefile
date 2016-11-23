CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		sdl_hello.o

LIBS = -lSDL

TARGET =	sdl_hello

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
