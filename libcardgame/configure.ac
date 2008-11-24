AC_INIT([libcardgame], [0.1], [Diogo Dutra <diogo.comp@gmail.com>])

AM_INIT_AUTOMAKE

AC_PROG_LIBTOOL
AC_PROG_CXX

libcardgame_includedir='${includedir}/libcardgame'
AC_SUBST(libcardgame_includedir)

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile src/Makefile libcardgame.pc])

PKG_CHECK_MODULES(XML_PARSER, xml_parser)
AC_SUBST(XML_PARSER_CFLAGS)
AC_SUBST(XML_PARSER_LIBS)

PKG_CHECK_MODULES(EINA, eina-0)
AC_SUBST(EINA_CFLAGS)
AC_SUBST(EINA_LIBS)

AC_OUTPUT
