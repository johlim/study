cmake_minimum_required(VERSION 3.10)
project(dbus_example)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${DBUS_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})

add_executable(dbus_server dbus_server.cpp)
target_link_libraries(dbus_server ${DBUS_LIBRARIES})

add_executable(dbus_client dbus_client.cpp)
target_link_libraries(dbus_client ${DBUS_LIBRARIES})

# 추가 컴파일 및 링크 플래그
target_compile_options(dbus_server PRIVATE ${DBUS_CFLAGS_OTHER})
target_compile_options(dbus_client PRIVATE ${DBUS_CFLAGS_OTHER})

target_link_options(dbus_server PRIVATE ${DBUS_LDFLAGS_OTHER})
target_link_options(dbus_client PRIVATE ${DBUS_LDFLAGS_OTHER})
