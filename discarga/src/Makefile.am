lib_LTLIBRARIES = libdiscarga.la
libdiscarga_la_SOURCES = \
	Deck.cpp	\
	Rule_Handler.cpp \
	Dealer.cpp	\
	Player.cpp
libdiscarga_la_CPPFLAGS = @XML_PARSER_CFLAGS@ @EINA_CFLAGS@ @IPCPP_CFLAGS@
libdiscarga_la_LIBADD = @XML_PARSER_LIBS@ @EINA_LIBS@ @IPCPP_LIBS@
libdiscarga_la_LDFLAGS = -version-info 0:1:0

discarga_include_HEADERS = \
	Card.h		\
	Player.h	\
	Rule.h		\
	Rule_Handler.h	\
	Dealer.h	\
	Deck.h
