# Note: plugindir is set in configure

##############################################################################
# TODO: change libgstplugin.la to something else, e.g. libmysomething.la     #
##############################################################################
plugin_LTLIBRARIES = libgstaudiofilterexample.la libgstvideofilterexample.la \
libgstvgagoldfilter.la libgstvgahorizontaledge.la libgstvgaratio.la \
libgstvgathreshold.la libgstrgbdemux.la

##############################################################################
# TODO: for the next set of variables, name the prefix if you named the .la, #
#  e.g. libmysomething.la => libmysomething_la_SOURCES                       #
#                            libmysomething_la_CFLAGS                        #
#                            libmysomething_la_LIBADD                        #
#                            libmysomething_la_LDFLAGS                       #
##############################################################################
## Plugin 1 (video filter example)

# sources used to compile this plug-in
libgstvideofilterexample_la_SOURCES = gstvideofilter.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstvideofilterexample_la_CFLAGS = $(GST_CFLAGS)
libgstvideofilterexample_la_LIBADD = $(GST_LIBS)
libgstvideofilterexample_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstvideofilterexample_la_LIBTOOLFLAGS = --tag=disable-static

## Plugin 2 (audio filter example)

# sources used to compile this plug-in
libgstaudiofilterexample_la_SOURCES = gstaudiofilter.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstaudiofilterexample_la_CFLAGS = $(GST_CFLAGS)
libgstaudiofilterexample_la_LIBADD = $(GST_LIBS)
libgstaudiofilterexample_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstaudiofilterexample_la_LIBTOOLFLAGS = --tag=disable-static

## Plugin 3 (vgagoldfilter)

# sources used to compile this plug-in
libgstvgagoldfilter_la_SOURCES = gstvgagoldfilter.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstvgagoldfilter_la_CFLAGS = $(GST_CFLAGS)
libgstvgagoldfilter_la_LIBADD = $(GST_LIBS)
libgstvgagoldfilter_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstvgagoldfilter_la_LIBTOOLFLAGS = --tag=disable-static

## Plugin 4 (vgahorizontaledge)

# sources used to compile this plug-in
libgstvgahorizontaledge_la_SOURCES = gstvgahorizontaledge.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstvgahorizontaledge_la_CFLAGS = $(GST_CFLAGS)
libgstvgahorizontaledge_la_LIBADD = $(GST_LIBS)
libgstvgahorizontaledge_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstvgahorizontaledge_la_LIBTOOLFLAGS = --tag=disable-static

## Plugin 5 (vgaratio)

# sources used to compile this plug-in
libgstvgaratio_la_SOURCES = gstvgaratio.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstvgaratio_la_CFLAGS = $(GST_CFLAGS)
libgstvgaratio_la_LIBADD = $(GST_LIBS)
libgstvgaratio_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstvgaratio_la_LIBTOOLFLAGS = --tag=disable-static

## Plugin 6 (threshold)

# sources used to compile this plug-in
libgstvgathreshold_la_SOURCES = gstvgathreshold.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstvgathreshold_la_CFLAGS = $(GST_CFLAGS)
libgstvgathreshold_la_LIBADD = $(GST_LIBS)
libgstvgathreshold_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstvgathreshold_la_LIBTOOLFLAGS = --tag=disable-static

## Plugin 6 (rgbdemux)

# sources used to compile this plug-in
libgstrgbdemux_la_SOURCES = gstrgbdemux.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstrgbdemux_la_CFLAGS = $(GST_CFLAGS)
libgstrgbdemux_la_LIBADD = $(GST_LIBS)
libgstrgbdemux_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstrgbdemux_la_LIBTOOLFLAGS = --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = gstplugin.h
