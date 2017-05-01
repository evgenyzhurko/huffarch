#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


AC_PREREQ([2.69])
AC_INIT([HuffArh], [1.0.0], [evgeny.zhurko@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_CONFIG_HEADERS([config.h])

AC_SUBST(CFLAGS)
if test "" = "$CFLAGS"; then
    CFLAGS=" "
fi

AC_SUBST(CXXFLAGS)
if test "" = "$CXXFLAGS"; then
    CXXFLAGS=" "
fi

# Checks for programs.
AC_PROG_CC([gcc])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_OUTPUT