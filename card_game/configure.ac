AC_INIT([card_game], [0.1], [Diogo Dutra <diogo.comp@gmail.com>])

AM_INIT_AUTOMAKE

AC_PROG_LIBTOOL
AC_PROG_CXX

card_game_includedir='${includedir}/card_game'
AC_SUBST(card_game_includedir)

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile src/Makefile card_game.pc])

PKG_CHECK_MODULES(XML_PARSER, xml_parser)
AC_SUBST(XML_PARSER_CFLAGS)
AC_SUBST(XML_PARSER_LIBS)

PKG_CHECK_MODULES(EINA, eina-0)
AC_SUBST(EINA_CFLAGS)
AC_SUBST(EINA_LIBS)

if test "x${prefix}" = "xNONE"; then
	AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${ac_default_prefix}/share/${PACKAGE}", [PACKAGE_DATA_DIR])
else
	AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${prefix}/share/${PACKAGE}", [PACKAGE_DATA_DIR])
fi


AC_OUTPUT
