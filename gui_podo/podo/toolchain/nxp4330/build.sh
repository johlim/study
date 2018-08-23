#!/bin/sh
export TOOLCHAIN_PATH=/home/jhlim/git_local/study/gui_podo/podo/toolchain/nxp4330
export TOOLCHAIN_FILE=$TOOLCHAIN_PATH/arm-cortex_a9-linux-gnueabi.cmake
export ROOT_PATH=/opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi/sysroot
export PATH=$ROOT_PATH/bin:$PATH
export CC=arm-cortex_a9-linux-gnueabi-gcc
export CXX=arm-cortex_a9-linux-gnueabi-g++
export SDLDIR=/opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi/sysroot/usr/include/SDL
export HISILICON=0
make
