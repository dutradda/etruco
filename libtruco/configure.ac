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

PKG_CHECK_MODULES(EINA, eina-0)
AC_SUBST(EINA_CFLAGS)
AC_SUBST(EINA_LIBS)

if test "x${prefix}" = "xNONE"; then
	AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${ac_default_prefix}/share/${PACKAGE}", [PACKAGE_DATA_DIR])
else
	AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${prefix}/share/${PACKAGE}", [PACKAGE_DATA_DIR])
fi


AC_OUTPUT
