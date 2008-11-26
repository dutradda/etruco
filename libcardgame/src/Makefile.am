lib_LTLIBRARIES = libcardgame.la
libcardgame_la_SOURCES = \
	Deck.cpp	\
	Card_Game.cpp
libcardgame_la_CPPFLAGS = @XML_PARSER_CFLAGS@ @EINA_CFLAGS@
libcardgame_la_LIBADD = @XML_PARSER_LIBS@ @EINA_LIBS@
libcardgame_la_LDFLAGS = -version-info 0:1:0

libcardgame_include_HEADERS = \
	Card.h		\
	Player.h	\
	Rule.h		\
	Team.h		\
	Card_Game.h	\
	Deck.h
