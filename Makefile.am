ACLOCAL_AMFLAGS= -I m4

AM_CXXFLAGS=-std=c++11 -I$(top_srcdir)/lib/include/public -I$(top_srcdir)/lib/include/private

lib_LTLIBRARIES=libsktest.la
bin_PROGRAMS=sktest

libsktest_la_CPPFLAGS = $(LIBCURL_CFLAGS) -Wall -Werror -Wpedantic

libsktest_la_SOURCES = \
	lib/src/sk/connectivity_test.cpp \
	lib/src/sk/connectivity_test_impl.cpp \
	lib/src/sk/http_header.cpp \
	lib/src/sk/connectivity_test_runner.cpp

sktest_LDADD = libsktest.la $(LIBCURL_LIBS)
	
sktest_SOURCES=app/main.cpp
