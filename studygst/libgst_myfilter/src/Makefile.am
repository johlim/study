plugin_LTLIBRARIES = libgst_myfilter.la

libgst_myfilter_la_SOURCES = gstmyfilter.c gstmyfilter.h

# compiler and linker flags used to compile this plugin, set in configure.ac
libgst_myfilter_la_CFLAGS = $(GST_CFLAGS)
libgst_myfilter_la_LIBADD = $(GST_LIBS)
libgst_myfilter_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgst_myfilter_la_LIBTOOLFLAGS = --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = gstmyfilter.h
