#######################################################
#
# Makefile for NextChip Board
#
#######################################################


########################################################################
# Get Linux Build Enviornment:
include ../../build.env
include Makefile.config

ARCHNAME        := nxp4330
#CROSSNAME       := arm-cortex_a9-linux-gnueabi-

KERNDIR         := ../../../kernel/kernel-3.4.39
ARCHDIR         := ../../../application

LIBSDIR         := $(ARCHDIR)/library
LIB_INSTALL     := $(LIBSDIR)/lib
INC_INSTALL     := $(LIBSDIR)/include
MODULES_DIR		:= $(ARCHDIR)/comm_test_app/modules
PORT_DIR		:= $(ARCHDIR)/comm_test_app/port

######################################################################
# NFS path
NFS_PATH = /nfs/$(shell whoami)/nvs3320/nand1/carblx
NFS_LIB_PATH = /nfs/$(shell whoami)/nvs3320/nand1/lib
NFS_COPY = n

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
ifdef V
	ifeq ("$(origin V)", "command line")
		BUILD_VERBOSE = $(V)
		Q =
	endif
endif

ifndef BUILD_VERBOSE
	BUILD_VERBOSE = 1
	Q = @
endif

export BUILD_VERBOSE Q

###############################################################################
# Target application
###############################################################################
TARGET_APP	= comm_test_app

###############################################################################
# LIBRARY
###############################################################################
#SYSROOT = /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi/sysroot
INCDIR += -I$(SYSROOT)/usr/include/glib-2.0
INCDIR += -I$(SYSROOT)/usr/lib/glib-2.0/include
LIBDIR += -L$(SYSROOT)/usr/lib
LIBDIR += -L$(LIBSDIR)/lib

#GTK
INCDIR += -pthread -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz
LIBS   += -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfontconfig -lgobject-2.0 -lglib-2.0 -lfreetype

#ETC
LIBS   += -lstdc++ -lasound

# GUI App

# MODULES
INCDIR += -I$(MODULES_DIR)/include
LIBDIR += -L$(MODULES_DIR)/lib

# PORT
INCDIR += -I$(PORT_DIR)/include
LIBDIR += -L$(PORT_DIR)/lib

#GLIB
LIBS	+= -lglib-2.0
###############################################################################
# ts lib
###############################################################################
#LIBDIR	+= -L$(LIBSDIR)/lib/tslib
#INCDIR	+= -I$(LIBSDIR)/include/tslib
#LIBS		+= -lts	# touch adjust library

###############################################################################
# 3rd-party link
###############################################################################
#LIBS	+= -lpng12				# png of gx library
#LIBS    += asound				# alsa audio static library
#LIBS	+= -lswjpeg			# s/w jpeg snapshot
#LIBS    += -lhwJpeg			# h/w jpeg snapshot

###############################################################################
# application include
###############################################################################
INCDIR	+= -I$(PROJ_HOME)
INCDIR  += -I$(PROJ_HOME)/comm


###############################################################################
# application link
###############################################################################
LIBS	+= -lpthread			# pthread library
#LIBS	+= -lrt
#LIBS	+= -lz					# z of gx library
LIBS	+= -lm

###############################################################################
# Custom
CUSTOMS += -UDM_UNITTEST
#
# Functions
# only choose one type(audio)

##################################################
#
# This is section camera config
#
##################################################

##############FRONT CAMERA CONFIG#################
ifeq ($(SUPPORT_CAMERATYPE_FRONT),"NVP6114")
DEFINES += -DSUPPROT_CAMERA_FRONT="\"nvp6114"\"
endif

ifeq ($(SUPPORT_CAMERATYPE_FRONT),"NVP2422")
DEFINES += -DSUPPROT_CAMERA_FRONT="\"nvp242x"\"
endif

ifeq ($(SUPPORT_CAMERATYPE_FRONT),"NVP2440")
DEFINES += -DSUPPROT_CAMERA_FRONT="\"nvp244x"\"
endif

ifeq ($(SUPPORT_CAMERATYPE_FRONT),"MIPIPLK")
DEFINES += -DSUPPROT_CAMERA_FRONT="\"mipiplk"\"
endif

##############REAR CAMERA CONFIG#################
ifeq ($(SUPPORT_CAMERATYPE_REAR),"NVP6114")
DEFINES += -DSUPPROT_CAMERA_REAR="\"nvp6114"\"
endif

ifeq ($(SUPPORT_CAMERATYPE_REAR),"NVP2422")
DEFINES += -DSUPPROT_CAMERA_REAR="\"nvp242x"\"
endif

ifeq ($(SUPPORT_CAMERATYPE_REAR),"NVP2440")
DEFINES += -DSUPPROT_CAMERA_REAR="\"nvp244x"\"
endif

##############REAR CAMERA CONFIG#################
ifeq ($(SUPPORT_CAMERATYPE_USB),"Y")
DEFINES += -DSUPPORT_UVC_CAMERA
endif

##################################################
#
# This is audiococodec config
#
##################################################


ifeq ($(SUPPORT_AUDIO_CODEC),"ALC5633")
DEFINES += -DSUPPORT_AUDIO_CODEC="\"alc5633"\" 
endif


################################################

DEFINES += $(CUSTOMS)

###############################################################################
#CFLAGS += -msoft-float -mfloat-abi=softfp 
CFLAGS := -g
CFLAGS += $(COPTS) $(INCDIR) $(DEFINES) -std=c99
CPPFLAGS += $(CPPOPTS) $(INCDIR) $(DEFINES) -std=gnu++11
LFLAGS = $(LIBDIR) $(LIBS)  -lsupc++

SUB_DIR=	`find ./ -type d`

###############################################################################
OBJECTS += main_builder.o \
		


###############################################################################
all: $(TARGET_APP) install

$(TARGET_APP) : $(OBJECTS) $(UILIB)
#	echo $(INCDIR)
	@echo "carblx Linking.....$(TARGET_APP) $(OBJECTS) $(LFLAGS) $(HALLIB) $(THIRDIB) $(UILIB) "
	$(Q)$(CPP) -o $(TARGET_APP) $(OBJECTS) $(LFLAGS) $(HALLIB) $(THIRDIB) $(UILIB)

%.o: %.c
ifeq ($(BUILD_VERBOSE),0)
	@echo "carblx c Compiling.....[$(CC) $(CFLAGS) $(INCLUDE)]	[$<]"
endif
	@$(Q)$(CC)  $(CFLAGS) $(INCLUDE) -c  -o $@ $<

%.o: %.cpp
ifeq ($(BUILD_VERBOSE),0)
	@echo "carblx cpp Compiling.....[$(CPP) $(CPPFLAGS) $(INCLUDE)]	[$<]"
endif
	$(Q)$(CPP) $(CPPFLAGS) $(INCLUDE) -c -o $@ $<

install:	$(TARGET_APP)
ifeq ($(NFS_COPY),y)
	$(Q)cp -f $(TARGET_APP) ${NFS_PATH}
	@echo "copying.nfs...	[OK]"
endif
ifeq ($(NAND_COPY),y)
	@cp -f $(TARGET_APP) ${NAND_PATH}
	@echo "copying.nand	[OK]"
endif
	@echo "Install.......	[OK]"

strip: $(TARGET_APP)
	@$(STRIP) $(TARGET_APP)
	@echo "strip $(TARGET_APP)[OK]"

clean:
	@for SDIR in $(SUB_DIR) ; do	\
		rm -f $${SDIR}/*.i;			\
		rm -f $${SDIR}/*.o;			\
		rm -f $${SDIR}/*.bak;		\
	done;

	@rm -f $(TARGET_APP)

	@echo "Cleaning......	[OK]"

tag:
	@ctags -R  *.c *.h ./ ../modules ../../library ./include ../port/src/opx_sdk
	@echo "Making tags...   [OK]"

touch:
	@find ./ -name "*.*" -print -exec touch {} \;
	@chmod -R 775 *

