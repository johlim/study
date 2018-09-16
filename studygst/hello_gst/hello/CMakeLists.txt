project(hello_gst)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -g -fpermissive")

set(CMAKE_CXX_COMPILER  arm-linux-gnueabihf-g++ )
set(CMAKE_C_COMPILER  arm-linux-gnueabihf-gcc )

find_package(PkgConfig REQUIRED)

pkg_search_module(GST REQUIRED gstreamer-1.0>=1.4 )

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
include_directories(
  ${GSTREAMER_INCLUDE_DIRS}
  ${GSTREAMER-APP_INCLUDE_DIRS}
  ${GSTREAMER-AUDIO_INCLUDE_DIRS}
  ${GSTREAMER-PBUTILS_INCLUDE_DIRS}
  ${GSTREAMER-FFT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GST_INCLUDE_DIRS}
)

link_directories(
  ${GSTREAMER_LIBRARY_DIRS}
  ${GSTREAMER-APP_LIBRARY_DIRS}
  ${GSTREAMER-AUDIO_LIBRARY_DIRS}
  ${GSTREAMER-PBUTILS_LIBRARY_DIRS}
  ${GSTREAMER-FFT_LIBRARY_DIRS}
)
set(inputtest_LIBRARIES
  ${GSTREAMER_LIBRARIES}
  ${GSTREAMER-APP_LIBRARIES}
  ${GSTREAMER-AUDIO_LIBRARIES}
  ${GSTREAMER-PBUTILS_LIBRARIES}
  ${GSTREAMER-FFT_LIBRARIES}
  ${GST_LIBRARIES} 
  pthread
  ${GLIB_LIBRARIES}
  ${GLIB_GIO_LIBRARIES}
  ${GLIB_GOBJECT_LIBRARIES}
)
set(inputtest_SOURCES
  main.c
)

#SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#add_subdirectory(src)
#add_subdirectory(demo)
add_executable(hello_gst ${inputtest_SOURCES})
target_link_libraries(hello_gst ${inputtest_LIBRARIES})
