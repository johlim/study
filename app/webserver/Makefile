ARCHNAME        := nxp4330
CROSSNAME       := arm-cortex_a9-linux-gnueabi-
#CROSSNAME       := 


#########################################################################
#	Toolchain.
##########################################################################

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

#########################################################################
# 	Target	
##########################################################################

TARGET_APP = wbserver

#########################################################################
# 	Library
##########################################################################

LIBS	+= -lpthread			# pthread library
DEFINES += -D_GNU_SOURCE
OBJECTS += webserver.o \

CFLAGS = $(INCDIR) $(DEFINES) -g -msoft-float
LFLAGS = $(LIBDIR) $(LIBS)


all: $(TARGET_APP)

$(TARGET_APP) : $(OBJECTS) 

	$(Q)$(CC) -o $(TARGET_APP) $(OBJECTS) $(LFLAGS)

clean:
	@for SDIR in $(SUB_DIR) ; do	\
		rm -f $${SDIR}/*.i;			\
		rm -f $${SDIR}/*.o;			\
		rm -f $${SDIR}/*.bak;		\
	done;

	@rm -f *.o
	@rm -f $(TARGET_APP)

	@echo "Cleaning......	[OK]"

