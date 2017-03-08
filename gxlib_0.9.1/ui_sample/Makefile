#
# falinux 라이블러리를 사용하는	어플용 Makefile
#

#CROSS_PREFIX	= mipsel-linux
#CROSS_PREFIX	= arm-linux
#CROSS_PREFIX   = arm-generic-linux-gnueabi
#CROSS_PREFIX	= arm-cortex_a9-linux-gnueabi
## 사용자 소스
TARGET			= app_gxlib
SRCS			= sample.c


#---------------------------------------------------------------------
## 소스레벨의 라이브러리
DIR_GXLIB		= ../lib/gxlib/
SRCS_GXLIB		= $(DIR_GXLIB)gx.c $(DIR_GXLIB)gxjpg.c $(DIR_GXLIB)gxbmp.c $(DIR_GXLIB)gxbdf.c $(DIR_GXLIB)fontinfo.c $(DIR_GXLIB)ksc5601.c	$(DIR_GXLIB)gximagelist.c $(DIR_GXLIB)gxmosaic.c $(DIR_GXLIB)gxlayer.c
#SRCS_GXLIB		+= $(DIR_GXLIB)gxpng.c 
SRCS			+= $(SRCS_GXLIB) 

#---------------------------------------------------------------------
## UI 소스
#DIR_UILIB		= ../state/
#SRCS_UILIB		= $(DIR_UILIB)obj_common.c $(DIR_UILIB)parser.c $(DIR_UILIB)state.c $(DIR_UILIB)list_if.c

#SRCS			+= $(SRCS_UILIB) 
#INCLUDEDIRS		+= -I$(DIR_UILIB)

## GLIB for UI
#SYSROOT += /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi/sysroot
INCDIR += -I$(SYSROOT)/usr/include/glib-2.0
INCDIR += -I$(SYSROOT)/usr/lib/glib-2.0/include

INCLUDEDIRS		+= $(INCDIR)
## UI 소스
#---------------------------------------------------------------------


## 인클루드	디렉토리
INCLUDEDIRS		+= -I. -I../include/gxlib

OBJS			= $(SRCS:.c=.o)

CFLAGS			= $(INCLUDEDIRS) -W -Wall -O2 -g
LIBS			= -lm -lz 
LIBS			+= -lglib-2.0
#LIBS			+= -ljpeg
#LIBS			+= -lpng12

#---------------------------------------------------------------------
CC				=	$(CROSS_PREFIX)-gcc
CXX				=	$(CROSS_PREFIX)-g++
AR				=	$(CROSS_PREFIX)-ar rc
AR2				=	$(CROSS_PREFIX)-ranlib
RANLIB			=	$(CROSS_PREFIX)-ranlib
LD				=	$(CROSS_PREFIX)-ld
NM				=	$(CROSS_PREFIX)-nm
STRIP			=	$(CROSS_PREFIX)-strip
OBJCOPY			=	$(CROSS_PREFIX)-objcopy
CP	= cp
MV	= mv
#--------------------------------------------------------------------

all	: $(TARGET) install

$(TARGET) :	$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o	$@ $(LIBS)
	$(NM) $(TARGET)	> $(TARGET).map

%.o:%.c
	@echo "Compiling $<	..."
	$(CC) -c $(CFLAGS) -o $@ $<

%.o:%.cc
	@echo "C++ compiling $<	..."
	$(CXX) -c $(CFLAGS)	$(CXXFLAGS)	-o $@ $<

dep	:
	$(CC) -M $(INCLUDEDIRS)	$(SRCS)	> .depend

clean:
	rm -f *.bak
	rm -f *.map
	rm -f *.o
	rm -f $(OBJS)
	rm -f $(TARGET)	core

distclean: clean
	rm -rf .depend

install: 
	cp $(TARGET) /nfs/jhlim/nvs3320/nand1 
	cp $(TARGET) /nfs/jhlim/nxp4330/nand1 


ifeq (.depend,$(wildcard .depend))
include	.depend
endif
