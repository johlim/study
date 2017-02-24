plugin_LTLIBRARIES = libgstmyfilter.la

libgstmyfilter_la_SOURCES = gstmyfilter.c gstmyfilter.h

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstmyfilter_la_CFLAGS = $(GST_CFLAGS)
libgstmyfilter_la_LIBADD = $(GST_LIBS)
libgstmyfilter_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstmyfilter_la_LIBTOOLFLAGS = --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = gstmyfilter.h
