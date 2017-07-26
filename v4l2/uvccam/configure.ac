dnl required version of autoconf
AC_PREREQ([2.53])

dnl TODO: fill in your package name and package version here
AC_INIT([uvccaputre],[0.0.0])

dnl required versions of gstreamer and plugins-base
GST_REQUIRED=1.0.0
GSTPB_REQUIRED=1.0.0

AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

dnl required version of automake
AM_INIT_AUTOMAKE([1.10])

dnl enable mainainer mode by default
AM_MAINTAINER_MODE([enable])

dnl check for tools (compiler etc.)
AC_PROG_CC

AC_PROG_CXX

GST_API_VERSION=1.0
AC_SUBST(GST_API_VERSION)
AC_DEFINE_UNQUOTED(GST_API_VERSION, "$GST_API_VERSION", [GStreamer API Version])

dnl required version of libtool
LT_PREREQ([2.2.6])
LT_INIT

dnl give error and exit if we don't have pkgconfig
AC_CHECK_PROG(HAVE_PKGCONFIG, pkg-config, [ ], [
                                           AC_MSG_ERROR([You need to have pkg-config installed!])
                                           ])

dnl Check for the required version of GStreamer core (and gst-plugins-base)
dnl This will export GST_CFLAGS and GST_LIBS variables for use in Makefile.am
dnl
dnl If you need libraries from gst-plugins-base here, also add:
dnl etc.
PKG_CHECK_MODULES(GST, [
                        gstreamer-1.0 >= $GST_REQUIRED
                        gstreamer-base-1.0 >= $GST_REQUIRED
                        gstreamer-controller-1.0 >= $GST_REQUIRED
                        ]
                  )

dnl check if compiler understands -Wall (if yes, add -Wall to GST_CFLAGS)
AC_MSG_CHECKING([to see if compiler understands -Wall])
save_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS -Wall"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([ ], [ ])], [
                   GST_CFLAGS="$GST_CFLAGS -Wall"
                   AC_MSG_RESULT([yes])
                   ], [
                       AC_MSG_RESULT([no])
                       ])
AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
                 ])
AC_OUTPUT


