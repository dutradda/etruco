AC_INIT([ipcpp], [0.1], [Diogo Dutra <diogo.comp@gmail.com>])

AM_INIT_AUTOMAKE

AC_PROG_LIBTOOL
AC_PROG_CXX

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile src/Makefile ipcpp.pc])

ipcpp_includedir='${includedir}/ipcpp'
AC_SUBST(ipcpp_includedir)

PKG_CHECK_MODULES(ECORE_IPC, ecore-ipc)
AC_SUBST(ECORE_IPC)
AC_SUBST(ECORE_IPC)

if test "x${prefix}" = "xNONE"; then
	AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${ac_default_prefix}/share/${PACKAGE}", [PACKAGE_DATA_DIR])
else
	AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${prefix}/share/${PACKAGE}", [PACKAGE_DATA_DIR])
fi


AC_OUTPUT
