AC_INIT([libtruco], [0.1], [Diogo Dutra <diogo.comp@gmail.com>])

AM_INIT_AUTOMAKE

AC_PROG_LIBTOOL
AC_PROG_CXX

libtruco_includedir='${includedir}/libtruco'
AC_SUBST(libtruco_includedir)

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile src/Makefile libtruco.pc])

PKG_CHECK_MODULES(LIBXML, libxml-2.0)
AC_SUBST(LIBXML_CFLAGS)
AC_SUBST(LIBXML_LIBS)

PKG_CHECK_MODULES(GMODULE, gmodule)
AC_SUBST(GMODULE_CFLAGS)
AC_SUBST(GMODULE_LIBS)

AC_OUTPUT
