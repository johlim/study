#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([cldvr], [0.0.1], [limjh@bokwang.com])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign])

GST_REQUIRED=0.10.16

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES(GST, [
    gstreamer-0.10              >= $GST_REQUIRED
    gstreamer-base-0.10         >= $GST_REQUIRED
    gstreamer-controller-0.10   >= $GST_REQUIRED
  ], [
    AC_SUBST(GST_CFLAGS)
    AC_SUBST(GST_LIBS)
  ], [
  AC_MSG_ERROR([
    Can't find the following GStreamer development packages:

      gstreamer-0.10              >= $GST_REQUIRED
      gstreamer-base-0.10         >= $GST_REQUIRED
      gstreamer-controller-0.10   >= $GST_REQUIRED

    Please make sure you have the necessary GStreamer-0.10
    development headers installed.

    On debian/Ubuntu systems you will probably need to install the
    'libgstreamer0.10-dev' and 'libgstreamer-plugins-base0.10-dev' packages.

    On RPM-based systems you will probably need to install the
    'gstreamer-devel-0.10' package.
  ])
])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_CHECKING([to see if compiler understands -Wall])
save_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS -Wall"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([ ], [ ])], [
  GST_CFLAGS="$GST_CFLAGS -Wall"
  AC_MSG_RESULT([yes])
], [
  AC_MSG_RESULT([no])
])

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday memset])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
