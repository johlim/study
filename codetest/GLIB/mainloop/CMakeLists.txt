cmake_minimum_required(VERSION 3.11)
project (aim_bt_service)

# Target name
set(target aim_bt_service)

set(CMAKE_BUILD_TYPE Release)

# Define
set(CMAKE_BUILD_TYPE Debug)
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)

#if (GLIB_PKG_FOUND)
#message(Found glib-2.0)
#endif (GLIB_PKG_FOUND)

# Includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../aim/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../system/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../aim_system/include
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${GLIB_PKG_INCLUDE_DIRS}
)

# Sources
file(GLOB_RECURSE public_headers
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.hpp)

file(GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# Build excutable
add_executable(${target} ${sources})

# Project options
set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    C_STANDARD 11
    CXX_STANDARD 11
    # reduce bin size
    #LINK_FLAGS_RELEASE -s
)

# Compile options
target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}
    ${DEFAULT_LIBRARIES}
    
   # cutils
   # log
   # aim
    pthread
   # bluetooth
   # crypto
    usb
    dbus-1
    udev
    ical
    readline
    ${GLIB_PKG_LIBRARIES}
    INTERFACE
)

# Install
install(TARGETS ${target} DESTINATION bin)
