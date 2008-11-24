lib_LTLIBRARIES = libipcpp.la
libipcpp_la_SOURCES = \
	Messages_Handler.cpp \
	Server.cpp \
	Client.cpp
libipcpp_la_CPPFLAGS = @XML_PARSER_CFLAGS@ @EINA_CFLAGS@
libipcpp_la_LDFLAGS = -version-info 0:1:0
libipcpp_la_LIBADD = @XML_PARSER_LIBS@ @EINA_LIBS@

ipcpp_include_HEADERS = \
	Messages_Handler.h \
	Server.h \
	Client.h
