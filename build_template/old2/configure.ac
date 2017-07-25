#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.57)
AC_INIT(a_out, 0.0.1, jhlim@plk.co.kr)
AM_INIT_AUTOMAKE([a_out], [0.0.1])
# AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([./src/exam.c])
# AM_CONFIG_HEADER(config.h)

PACKAGE_DESCRIPTION="jhlim tools check "
AC_SUBST(PACKAGE_DESCRIPTION)

# Set our default flags variables
#TS_DEFAULT_FLAGS

# Checks for programs.
#AC_PROG_CXX
AC_PROG_CC
#AC_PROG_CPP
#AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen])
AC_CHECK_LIB([pthread], [pthread_create])

# Checks for header files.
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h limits.h stdlib.h string.h time.h sys/ioctl.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME

# Checks for library functions.
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([bzero gettimeofday memmove memset munmap select strcasecmp strchr strdup strtoul])

# filters
AC_MSG_CHECKING([whether variance module is requested])
AC_ARG_ENABLE(variance,
	AS_HELP_STRING([--enable-variance],
		[Enable building of variance filter (default=yes)]),
	[variance_module=$enableval],
	[variance_module=yes])
AC_MSG_RESULT($variance_module)


AC_MSG_CHECKING([whether pthres module is requested])
AC_ARG_ENABLE(pthres,
	AS_HELP_STRING([--enable-pthres],
		[Enable building of pthres filter (default=yes)]),
	[pthres_module=$enableval],
	[pthres_module=yes])
AC_MSG_RESULT($pthres_module)



# hardware access modules
AC_MSG_CHECKING([whether to enable debugging])
AC_ARG_ENABLE(debug,
	AS_HELP_STRING(--enable-debug
		Enable debug messages from filters (default=no)), 
	,
	[enable_debug="no"])
AC_MSG_RESULT($enable_debug)
if test "$enable_debug" = "yes"; then
	DEBUGFLAGS="-g -ggdb -DDEBUG"
else
	DEBUGFLAGS=""
fi
AC_SUBST(DEBUGFLAGS)

LIBFLAGS="-DTSLIB_INTERNAL"
AC_SUBST(LIBFLAGS)

# Library versioning
LT_RELEASE=1.0
LT_CURRENT=1
LT_REVISION=1
LT_AGE=1
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
