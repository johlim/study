# Set the target architecture
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set the cross-compiling toolchain prefix
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_C_COMPILER arm-cortex_a9-linux-gnueabi-gcc)
#set(CMAKE_CXX_COMPILER arm-cortex_a9-linux-gnueabi-g++)

# Set the path to the cross-compiling system's root filesystem
#set(CMAKE_SYSROOT /opt/crosstools/arm-cortex_a9-eabi-4.7-eglibc-2.18/arm-cortex_a9-linux-gnueabi/sysroot)
set(CMAKE_SYSROOT )

# Set additional compiler and linker flags as necessary
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L $(CMAKE_SYSROOT)/usr/lib")

# Set any necessary system-specific settings
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
