noinst_LTLIBRARIES = liblocalcard_game.la
liblocalcard_game_la_SOURCES = \
	Card_Game.cpp
liblocalcard_game_la_CPPFLAGS = @XML_PARSER_CFLAGS@ @EINA_CFLAGS@
liblocalcard_game_la_LIBADD = @XML_PARSER_LIBS@ @EINA_LIBS@

lib_LTLIBRARIES = libcard_game.la
libcard_game_la_SOURCES = \
	Deck.cpp
libcard_game_la_LDFLAGS = -version-info 0:1:0
libcard_game_la_LIBADD = liblocalcard_game.la

libcard_game_include_HEADERS = \
	Card.h		\
	Player.h	\
	Rule.h		\
	Team.h		\
	Card_Game.h	\
	Deck.h
