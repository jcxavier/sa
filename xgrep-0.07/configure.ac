dnl autoconf source for XGrep installation
dnl Brendt Wohlberg
dnl Most recent modification: 14 September 2007

dnl Process this file with autoconf to produce a configure script.
AC_INIT(xgrep.c)

AC_LANG_C

dnl Check for C compiler
AC_PROG_CC
if test "$GCC" = "yes"; then
  CFLAGS="$CFLAGS -Wall -ansi -pedantic"
fi

AC_PROG_INSTALL

dnl Find path to sh
AC_PATH_PROG(SH, sh)

dnl Find path to rm
AC_PATH_PROG(RM, rm)

dnl Find path to makedepend
AC_PATH_PROG(MAKEDEPEND, makedepend)

dnl Find path to man2html
AC_PATH_PROG(MAN2HTML, man2html)

dnl Find path to valgrind
AC_PATH_PROG(VALGRIND, valgrind)

dnl libxml2 configuration flags
AC_PATH_PROG(XML2CONF, xml2-config)
CFLAGS="$CFLAGS `$XML2CONF --cflags`"
LDFLAGS="$LDFLAGS `$XML2CONF --libs`"


AC_MSG_CHECKING(whether libxml2 headers are available)
AC_TRY_COMPILE([
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/catalog.h>
#include <libxml/xpath.h>
],
[
xmlDocPtr doc = 0;
xmlNodePtr node = 0;
],
AC_MSG_RESULT(yes),
[AC_MSG_RESULT(no); AC_MSG_ERROR(libxml2 headers not found)]
)

AC_MSG_CHECKING(whether libxml2 library is available)
AC_TRY_LINK([
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/catalog.h>
#include <libxml/xpath.h>
],
[
xmlDocPtr doc = xmlNewDoc((xmlChar*)"1.0");
],
AC_MSG_RESULT(yes),
[AC_MSG_RESULT(no); AC_MSG_ERROR(libxml2 library not found)]
)


AC_MSG_CHECKING(whether libxml2 library is recent enough)
AC_TRY_COMPILE([
#include <libxml/xmlversion.h>
],
[
#if LIBXML_VERSION < 20422
#error libxml version not recent
#endif
],
AC_MSG_RESULT(yes),
[AC_MSG_RESULT(no); AC_MSG_ERROR(libxml2 library is earlier than 2.4.22)]
)


dnl pcre configuration flags
PCREOK="no"
CFLAGSTMP=$CFLAGS
LDFLAGSTMP=$LDFLAGS
AC_PATH_PROG(PCRECONF, pcre-config)
if test "$PCRECONF" != ""; then
  CFLAGS="$CFLAGS `$PCRECONF --cflags`"
  LDFLAGS="$LDFLAGS `$PCRECONF --libs`"
  PCREOK="yes"

  AC_MSG_CHECKING(whether pcre header is available)
  AC_TRY_COMPILE([
  #include <pcre.h>
  ],
  [
  pcre *re = 0;
  ],
  AC_MSG_RESULT(yes),
  [AC_MSG_RESULT(no); PCREOK="no"]
  )

  AC_MSG_CHECKING(whether pcre library is available)
  AC_TRY_LINK([
  #include <pcre.h>
  ],
  [
    pcre *p = pcre_compile("A*", 0, 0, 0, 0);
  ],
  AC_MSG_RESULT(yes),
  [AC_MSG_RESULT(no); PCREOK="no"]
  )
fi

if test "$PCREOK" = "yes"; then
  USE_PCRE=1
else
  USE_PCRE=0
  CFLAGS=$CFLAGSTMP
  LDFLAGS=$LDFLAGSTMP
fi
AC_SUBST(USE_PCRE)

dnl Find paths to package build tools
AC_PATH_PROG(RPM, rpm)
AC_PATH_PROG(RPMBUILD, rpmbuild)
AC_PATH_PROG(RPMLINT, rpmlint)
AC_PATH_PROG(DEBUILD, debuild)
AC_PATH_PROG(DEBSIGN, debsign)
AC_PATH_PROG(DEBSIGS, debsigs)

dnl Determine version number
PKGVERSION=`cat version`

dnl Configure package build information
if test -d "redhat"; then
  rpmver=`grep 'Version:' redhat/xgrep.spec | cut -f 2`
  rpmrel0=`grep 'Release:' redhat/xgrep.spec | cut -f 2`
  rpmrel=`rpm --eval "$rpmrel0"`
  RPMVER=$rpmver-$rpmrel
  RPMARCH=`rpmbuild --showrc | grep '^build arch' | cut -d ':' -f 2`
fi
if test -d "debian"; then
  DEBVER=`grep -o '^xgrep *(@<:@^()@:>@*)' debian/changelog | head -n 1 | \
	     sed -e 's/xgrep (\(.*\))/\1/'`
  DEBARCH=`dpkg-architecture 2>/dev/null | grep 'DEB_BUILD_ARCH=' | \
	     sed -e 's/DEB_BUILD_ARCH=//'`
fi

AC_SUBST(PKGVERSION RPMVER RPMARCH DEBVER DEBARCH)
AC_OUTPUT(Makefile)
