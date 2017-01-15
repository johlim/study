#***************************************************************************
#*       
#*	 
#***************************************************************************
#include ../build.env
PROJ_HOME       = `pwd`
OBJTREE                 = $(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))

CROSSNAME      = arm-cortex_a9-linux-gnueabi-

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
CFLAGS          := $(COPTS)  -std=c99
CPPFLAGS        := $(CPPOPTS)
AFLAGS          :=

ARFLAGS         := crv
LDFLAGS         :=
#LIBRARY         :=-L/opt/libjpeg-turbo/lib64 -ljpeg #-lturbojpeg -ljpeg
#LIBRARY         :=-L/opt/libjpeg-turbo/lib64 -lturbojpeg
#INCLUDE		:=-I/opt/libjpeg-turbo/include/ $(INCLUDE)
LIBRARY         :=-lturbojpeg

EXE = doturbojpeg
COMMON_INCLUDE = ./ 
CPP		:= g++
#ARM
SYSROOT		:= /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi/sysroot
CROSSNAME       := arm-cortex_a9-linux-gnueabi-
######################################################################
# NFS path
NFS_PATH = /nfs/$(shell whoami)/nvs3320/fcw
NFS_LIB_PATH = /nfs/$(shell whoami)/nvs3320/nand1/lib
NFS_COPY = y

#########################################################################
#	Toolchain.
#########################################################################
CROSS 	 	:= $(CROSSNAME)
CC			:= $(CROSS)gcc
CPP			:= $(CROSS)g++
AR			:= $(CROSS)ar
AS			:= $(CROSS)as
LD			:= $(CROSS)ld
NM			:= $(CROSS)nm
RANLIB		:= $(CROSS)ranlib
OBJCOPY		:= $(CROSS)objcopy
STRIP		:= $(CROSS)strip

###############################################################################
# LIBRARY
###############################################################################
INCDIR += -I$(SYSROOT)/usr/include
LIBDIR += -L$(SYSROOT)/usr/lib
#LIBDIR += -L./


CFLAGS = $(INCDIR) $(DEFINES) -g -O0
LFLAGS = $(LIBDIR) $(LIBS)  $(LIBRARY)

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
	tj_main.o\
	


all: makeall install
	
makeall: $(EXE)

$(EXE):	$(ALL_OBJS)
	$(CC) -g -o $(EXE) $(ALL_OBJS) $(LFLAGS)

#jpegutil.o:	jpegutil.c \
#	$(COMMON_INCLUDE)
#	$(CC) -c -g $(INCLUDE) jpegutil.c -o jpegutil.o -std=c99

install:	$(EXE)
ifeq ($(NFS_COPY),y)
	$(Q)cp -f $(EXE) ${NFS_PATH}
	echo "cp -f $(EXE) ${NFS_PATH} "
	@echo "copying.nfs...	[OK]"
endif

#install: $(EXE)
#	mv $(EXE) ~/bin
clean:
	rm -f $(ALL_OBJS)
	rm -f $(EXE)

tag:
	ctags -aR /opt/libjpeg-turbo/ /opt/libjpeg-turbo/include/ ./
