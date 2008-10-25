lib_LTLIBRARIES = liblibtruco.la
liblibtruco_la_SOURCES = \
	Rule.cpp       \
	Team.cpp       \
	Player.cpp       \
	Truco.cpp       \
	Deck.cpp
liblibtruco_la_LDFLAGS = -version-info 0:0:0

liblibtruco_la_CPPFLAGS = @LIBXML_CFLAGS@ @GMODULE_CFLAGS@

liblibtruco_la_LIBADD = @LIBXML_LIBS@ @GMODULE_LIBS@

libtruco_include_HEADERS = \
	Card.h           \
	Player.h           \
	Rule.h           \
	Team.h           \
	Truco.h           \
	Deck.h           \
	Deck_Baralho_Sujo.h
