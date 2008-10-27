noinst_LTLIBRARIES = libtruco.la
libtruco_la_SOURCES = \
	Truco.cpp
libtruco_la_CPPFLAGS = @LIBXML_CFLAGS@ @GMODULE_CFLAGS@
libtruco_la_LIBADD = @LIBXML_LIBS@ @GMODULE_LIBS@

lib_LTLIBRARIES = liblibtruco.la
liblibtruco_la_SOURCES = \
	Player.cpp	\
	Deck.cpp
liblibtruco_la_LDFLAGS = -version-info 0:0:0
liblibtruco_la_LIBADD = libtruco.la

libtruco_include_HEADERS = \
	Card.h		\
	Player.h	\
	Rule.h		\
	Team.h		\
	Truco.h		\
	Deck.h
