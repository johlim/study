bin_PROGRAMS = hello_gtk
hello_gtk_SOURCES = hello_gtk.h hello_gtk.c gui_core.c
#lib_LIBRARYIES = libhello_gtk.a
#libhello_gtk_a_SOURCES = gui_core.c hello_gtk.h

# compiler and linker flags used to compile this plugin, set in configure.ac
CFLAGS = $(GTK_CFLAGS) $(GTK_LIBS)

# headers we need but don't want installed
noinst_HEADERS = hello_gtk.h

clean : 
	-rm -rf *.o *.a hello_gtk
	@echo "removed all"
