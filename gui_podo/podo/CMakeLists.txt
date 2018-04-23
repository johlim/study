project(podo)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER  /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/bin/arm-cortex_a9-linux-gnueabi-g++)
set(CMAKE_C_COMPILER  /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/bin/arm-cortex_a9-linux-gnueabi-gcc)
#set(CMAKE_FIND_ROOT_PATH  /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18 )
set(CMAKE_FIND_ROOT_PATH  "/opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi/sysroot" )
# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "-g -Wall -O2 -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "-g -Wall -O2 -fno-omit-frame-pointer")

add_subdirectory(src)
add_subdirectory(demo)
#add_subdirectory(examples)

