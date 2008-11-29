lib_LTLIBRARIES = libipcpp.la
libipcpp_la_SOURCES = \
	Server.cpp \
	Client.cpp
libipcpp_la_CPPFLAGS = @ECORE_IPC_CFLAGS@
libipcpp_la_LDFLAGS = -version-info 0:1:0
libipcpp_la_LIBADD = @ECORE_IPC_LIBS@

ipcpp_include_HEADERS = \
	Server.h \
	Client.h
