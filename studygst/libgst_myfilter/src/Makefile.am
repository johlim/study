plugin_LTLIBRARIES = libgstmyldws.la

libgstmyldws_la_SOURCES = gstmyfilter.c gstmyfilter.h

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstmyldws_la_CFLAGS = $(GST_CFLAGS)
libgstmyldws_la_LIBADD = $(GST_LIBS)
libgstmyldws_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstmyldws_la_LIBTOOLFLAGS = --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = gstmyfilter.h
