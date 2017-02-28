# Note: plugindir is set in configure

##############################################################################
# TODO: change libgstplugin.la to something else, e.g. libmysomething.la     #
##############################################################################
plugin_LTLIBRARIES = libgstadaspump.la

##############################################################################
# TODO: for the next set of variables, name the prefix if you named the .la, #
#  e.g. libmysomething.la => libmysomething_la_SOURCES                       #
#                            libmysomething_la_CFLAGS                        #
#                            libmysomething_la_LIBADD                        #
#                            libmysomething_la_LDFLAGS                       #
##############################################################################

## Plugin 1

# sources used to compile this plug-in
libgstadaspump_la_SOURCES = gstadaspump.c gstadaspump.h

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstadaspump_la_CFLAGS = $(GST_CFLAGS)
libgstadaspump_la_LIBADD = $(GST_LIBS)
libgstadaspump_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstadaspump_la_LIBTOOLFLAGS = --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = gstadaspump.h
