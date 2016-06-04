message(STATUS "downloading...
     src='http://pngquant.org/libimagequant-2.0.0-src.tar.bz2'
     dst='/home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-2.0.0-src.tar.bz2'
     timeout='none'")

file(DOWNLOAD
  "http://pngquant.org/libimagequant-2.0.0-src.tar.bz2"
  "/home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-2.0.0-src.tar.bz2"
  SHOW_PROGRESS
  # no EXPECTED_MD5
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://pngquant.org/libimagequant-2.0.0-src.tar.bz2' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
