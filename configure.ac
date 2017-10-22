#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([sk-test], [0.1], [www.samknows.com])
#AC_SUBST(UHCPP_MODULE_NAME, [uhcpp])
#AC_SUBST(UHCPP_LIB_NAME, [libuhcpp])

AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([subdir-objects -Wno-portability])
LT_INIT([disable-static])
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL
#AC_CONFIG_SRCDIR([src/ws_service.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
PKG_CHECK_MODULES([LIBCURL], [libcurl])
PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4])
#PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4 giomm-2.4])
#PKG_CHECK_MODULES([LIBSODIUM], [libsodium])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
