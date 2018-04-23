
set(CMAKE_CXX_COMPILER  /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/bin/arm-cortex_a9-linux-gnueabi-g++)
set(CMAKE_C_COMPILER  /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/bin/arm-cortex_a9-linux-gnueabi-gcc)
set(CMAKE_FIND_ROOT_PATH  /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18 )
# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

