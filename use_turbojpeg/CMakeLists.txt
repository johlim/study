cmake_minimum_required(VERSION 3.0)

project(doturbojpeg)

set(SOURCE_FILES
    tj_main.c
    jpegutil.c
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")


add_executable(doturbojpeg ${SOURCE_FILES})

target_link_libraries(doturbojpeg
    jpeg
    turbojpeg
)