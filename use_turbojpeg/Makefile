#***************************************************************************
#*       Copyright (c) 2010 Aces Technology Co., Ltd.
#*	 Lee Sung Ho
#***************************************************************************
PROJ_HOME       = `pwd`
OBJTREE                 = $(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))

CROSSNAME      =

CC              =       $(CROSSNAME)gcc
LD              =       $(CROSSNAME)ld
AR              =       $(CROSSNAME)ar cqs 
STRIP   =       $(CROSSNAME)strip

CP              =       @cp -f
RM              =       @rm -f
LN              =       @ln -sf 
ECHO    =       @echo
CTAG    =       @ctags -R

BUILD_VERBOSE = 0 
Q = @
#########################################################################
#       Build Options
#########################################################################
#OPTS            := -fPIC -O2 -g -w
OPTS            := -fPIC -O0 -g -w
CPPOPTS         := $(OPTS) -Wnon-virtual-dtor

CFLAGS          := $(COPTS)
CPPFLAGS        := $(CPPOPTS)
AFLAGS          :=

ARFLAGS         := crv
LDFLAGS         :=
#LIBRARY         :=-L/opt/libjpeg-turbo/lib64 -ljpeg #-lturbojpeg -ljpeg
LIBRARY         :=-L/opt/libjpeg-turbo/lib64 -lturbojpeg
INCLUDE		:=-I/opt/libjpeg-turbo/include/ $(INCLUDE)

EXE = doturbojpeg
COMMON_INCLUDE = ./ 

#########################################################################
#       Generic Rules
#########################################################################
%.o: %.c
	        @echo "Compiling.....   [$<]" 
		        $(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

%.o: %.s
	        @echo "Compiling.....   [$<]"
		        @$(AS) $(AFLAGS) $(INCLUDE) -c -o $@ $<

%.o: %.cpp
	        @echo "Compiling.....   [$<]"
		        @$(CPP) $(CPPFLAGS) $(INCLUDE) -c -o $@ $<
#########################################################################
#       Generic Rules
#########################################################################

ALL_OBJS = \
	main.o\
	jpegutil.o	


all: makeall
	
makeall: $(EXE)

$(EXE):	$(ALL_OBJS)
	$(CC) -g -o $(EXE) $(ALL_OBJS) -static $(LIBRARY) 

jpegutil.o:	jpegutil.c \
	$(COMMON_INCLUDE)
	gcc -c -g $(INCLUDE) jpegutil.c -o jpegutil.o


install: $(EXE)
	mv $(EXE) ~/bin
clean:
	rm -f $(ALL_OBJS)
	rm -f $(EXE)

tag:
	ctags -aR /opt/libjpeg-turbo/ ./
