lib_LTLIBRARIES=libhello.la
libhello_la_SOURCES=hello.h hello.cpp
libhello_la_LDFLAGS=-version-info 0:0:0

#libtruco_includedir=$(includedir)/libtruco
libtruco_include_HEADERS=hello.h

bin_PROGRAMS=hello
hello_SOURCES=main.cpp
hello_LDADD=libhello.la
