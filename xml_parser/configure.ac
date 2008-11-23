AC_INIT([xml_parser], [0.1], [Diogo Dutra <diogo.comp@gmail.com>])

AM_INIT_AUTOMAKE

AC_PROG_LIBTOOL
AC_PROG_CXX

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile src/Makefile xml_parser.pc])

PKG_CHECK_MODULES(LIBXML, libxml-2.0)
AC_SUBST(LIBXML_CFLAGS)
AC_SUBST(LIBXML_LIBS)

AC_OUTPUT
