noinst_LTLIBRARIES = liblocalcardgame.la
liblocalcardgame_la_SOURCES = \
	Card_Game.cpp
liblocalcardgame_la_CPPFLAGS = @XML_PARSER_CFLAGS@ @EINA_CFLAGS@
liblocalcardgame_la_LIBADD = @XML_PARSER_LIBS@ @EINA_LIBS@

lib_LTLIBRARIES = libcardgame.la
libcardgame_la_SOURCES = \
	Deck.cpp
libcardgame_la_LDFLAGS = -version-info 0:1:0
libcardgame_la_LIBADD = liblocalcardgame.la

libcardgame_include_HEADERS = \
	Card.h		\
	Player.h	\
	Rule.h		\
	Team.h		\
	Card_Game.h	\
	Deck.h
