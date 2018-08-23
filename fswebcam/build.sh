#!/bin/bash
#/opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/bin/arm-cortex_a9-linux-gnueabi-
# architecture prefix
ARCH="arm-cortex_a9-linux-gnueabi"

# path to the toolchain and kernel base
TOOL_PATH=/opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18

#/opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi
# path to the toolchain base
BASE_PATH=$TOOL_PATH
INSTALL_PATH=$TOOL_PATH
#INSTALL_PATH=$TOOL_PATH/$ARCH

# cumulative toolchain prefix
PREFIX=$BASE_PATH/bin/$ARCH

export CC=$PREFIX-gcc
export CXX=$PREFIX-g++
export LD=$PREFIX-ld
export NM="$PREFIX-nm -B"
export AR=$PREFIX-ar
export RANLIB=$PREFIX-ranlib
export STRIP=$PREFIX-strip
export OBJCOPY=$PREFIX-objcopy
export LN_S="ln -s"

export CFLAGS="-g -O2 -I$BASE_PATH/include"
export CPPFLAGS="-I$BASE_PATH/include"
export CXXFLAGS=""
#/opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/lib/gcc/arm-cortex_a9-linux-gnueabi/4.7.4/
export LDFLAGS="-L$BASE_PATH/lib -L$BASE_PATH/$ARCH/lib -L$BASE_PATH/lib/gcc/$ARCH/4.7.4"

PATH=$BASE_PATH/bin:$PATH
./configure \
    --host=$ARCH \
    --prefix=$INSTALL_PATH\
    --with-png=$BASE_PATH \
    --with-jpeg=no \
    --with-freetype=no \
    --with-fontconfig=no \
    --with-xpm=no
