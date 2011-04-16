# Makefile for XGrep
# Most recent modification: 14 September 2007

prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
datadir = ${datarootdir}/xgrep
bindir = ${exec_prefix}/bin
mandir = ${datarootdir}/man

SHELL = /bin/sh
RM = /bin/rm
INSTALL = /usr/bin/install -c
MAKEDEPEND = /usr/X11/bin/makedepend
MAN2HTML = 
VALGRIND = 
RPM = 
RPMBUILD = 
RPMLINT = 
DEBUILD = 
DEBSIGN = 
DEBSIGS = 

CC=gcc
CFLAGS=-g -O2 -Wall -ansi -pedantic -I/usr/include/libxml2 -DXGREPVERSION=\"0.07\" -DUSE_PCRE=0
LDFLAGS= -lxml2 -lz -lpthread -licucore -lm
LIBS=

MODSRC = treex.c parsex.c debug.c find.c
MODHDR = $(MODSRC:%.c=%.h)
MODOBJ = $(MODSRC:%.c=%.o)
EXESRC = xgrep.c
EXEOBJ = $(EXESRC:%.c=%.o)
EXE = $(EXESRC:%.c=%)

MANSRC = xgrep.1
MANHTML = $(MANSRC:%.1=%.html)

DISTFILES = configure.ac configure Makefile.in install-sh \
            README INSTALL GPL ChangeLog NEWS version \
	    $(MODSRC) $(MODHDR) $(EXESRC) $(MANSRC)

PKGNAME = xgrep
VERSION = 0.07
DISTDIR = ${PKGNAME}-${VERSION}
DISTTGZ = dist/${DISTDIR}.tar.gz
RPMVER = 
RPMBASE = ${PKGNAME}-${RPMVER}
RPMARCH = 
DISTRPM = dist/${RPMBASE}.src.rpm dist/${RPMBASE}.${RPMARCH}.rpm
DEBVER = 
DEBBASE = ${PKGNAME}_${DEBVER}
DEBARCH = 
DISTDEB = dist/${PKGNAME}_${VERSION}.orig.tar.gz dist/${DEBBASE}.diff.gz \
	  dist/${DEBBASE}.dsc dist/${DEBBASE}_${DEBARCH}.deb


.PHONY: all manhtml check test clean distclean install uninstall dist\
        dist-rpm dist-rpm-sign dist-deb dist-deb-sign

.SUFFIXES: .1 .html


all: depend ${MODOBJ} ${EXEOBJ} ${EXE}

${EXE}: ${MODOBJ}

clean:
	@${RM} -f ${EXE} ${EXEOBJ} ${MODOBJ} ${MANHTML} *.o .test.stamp

distclean: clean
	@${RM} -f config.* Makefile Makefile.bak; ${RM} -rf dist

check:	test

test:	.test.stamp

.test.stamp: ${DISTFILES}
	@if [ "${VALGRIND}" = '' ]; then\
	  echo "Required tool valgrind is not available";\
	  exit 1;\
	fi;\
	echo "Checking xgrep memory allocation with valgrind";\
	echo "<a><b><c>1000</c><d>abc</d></b><b><c>2000</c><d>xyz</d></b>\
               <b><c>2001</c><d>xyz</d></b></a>" > tmp.xml; \
	vgresult=`${VALGRIND} --leak-check=yes --show-reachable=yes \
		   ./xgrep -s b:c/1/,d/x/ tmp.xml 2>&1 1>/dev/null`;\
	vgerror=`echo "$$vgresult" | grep "ERROR SUMMARY:" | \
		   awk '{print $$4}'`;\
        vgdlost=`echo "$$vgresult" | grep "==    definitely lost:" | \
		   awk '{print $$4}'`;\
        vgplost=`echo "$$vgresult" | grep "==    possibly lost:" | \
		   awk '{print $$4}'`;\
        vgreach=`echo "$$vgresult" | grep "==    still reachable:" | \
		   awk '{print $$4}'`;\
        if [ "$${vgerror:-0}" -gt 0 ] || [ "$${vgdlost:-0}" -gt 0 ] ||\
           [ "$${vgplots:-0}" -gt 0 ] || [ "$${vgreach:-0}" -gt 0 ]; then\
         echo "$$vgresult";\
	else\
	 echo No memory allocation errors found;\
        fi;\
	${RM} tmp.xml;\
	touch .test.stamp

install:
	@echo "Installing executable in ${DESTDIR}${bindir}";\
	if [ ! -d ${DESTDIR}${bindir} ];\
	  then ${INSTALL} -d ${DESTDIR}${bindir};\
	fi;\
	${INSTALL} ${EXE} ${DESTDIR}${bindir};\
	echo "Installing man page in ${DESTDIR}${mandir}";\
	if [ ! -d ${DESTDIR}${mandir} ]; then\
	  ${INSTALL} -d ${DESTDIR}${mandir};\
	fi;\
	if [ ! -d ${DESTDIR}${mandir}/man1 ];\
	  then ${INSTALL} -d ${DESTDIR}${mandir}/man1;\
	fi;\
	${INSTALL} -m 644 ${MANSRC} ${DESTDIR}${mandir}/man1

uninstall:
	@echo "Uninstalling executable in ${DESTDIR}${bindir}";\
	for exe in ${EXE}; do\
	  ${RM} -f ${DESTDIR}${bindir}/$$exe;\
	done;\
	echo "Uninstalling man pages\ in ${mandir}";\
	for man in ${MANSRC}; do\
	  ${RM} -f ${DESTDIR}${mandir}/man1/$$man;\
	done

manhtml: ${MANHTML}

depend:
	@if [ "${MAKEDEPEND}" = '' ]; then\
	  echo "Required tool makedepend is not available";\
	  exit 1;\
	fi;\
	${MAKEDEPEND} -- $(CFLAGS) -- $(MODHDR) $(MODSRC) >/dev/null 2>&1;\
	sed -e '/^# DO NOT DELETE/,$$ { /^.*\.o:/s+/[^\ ]*++g; }'\
	    -e '/^# DO NOT DELETE/,$$ { /^.*\.o:[ ]*$$/d; }' Makefile\
	    > Makefile.tmp;\
	mv Makefile.tmp Makefile

.c.o:
	${CC} -c $< ${CFLAGS}

.o: 
	${CC} -o $@  $< ${MODOBJ} ${LDFLAGS}

.1.html:
	@if [ "${MAN2HTML}" = '' ]; then\
	  echo "Required tool man2html is not available";\
	  exit 1;\
	fi;\
	${MAN2HTML} $< | sed 's+Content-type: text/html+<\!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">+' > $@


dist: ${DISTTGZ} test

${DISTTGZ}: ${DISTFILES}
	@${RM} -rf ${DISTTGZ} dist/${DISTDIR};\
	mkdir -p dist/${DISTDIR};\
	(tar cf - ${DISTFILES}) | (cd dist/${DISTDIR} && tar xfp -);\
	(cd dist; tar -cf ${DISTDIR}.tar ./${DISTDIR};\
	gzip -9 ${DISTDIR}.tar);\
	${RM} -rf dist/${DISTDIR}

dist-rpm: ${DISTRPM}

%${RPMVER}.src.rpm %${RPMVER}.${RPMARCH}.rpm: %${VERSION}.tar.gz
	@if [ "${RPMBUILD}" != '' -a -d redhat ]; then\
	  cp redhat/rpm* redhat/${PKGNAME}.spec dist;\
          mkdir -p dist/rpmbuild/BUILD dist/rpmbuild/tmp \
		   dist/rpmbuild/SRPMS dist/rpmbuild/RPMS;\
          cp ${DISTTGZ} dist/rpmbuild;\
	  cd dist;\
          ${RPMBUILD} -ba --rcfile rpmrc ${PKGNAME}.spec;\
          cp rpmbuild/RPMS/*.rpm rpmbuild/SRPMS/*.rpm .;\
          ${RM} -rf rpmbuild rpmmacros rpmrc ${PKGNAME}.spec;\
	  if [ "${RPMLINT}" != '' ]; then\
	    ${RPMLINT} -v *.rpm;\
	  fi;\
	else\
	  echo "Cannot build RPM packages";\
	  exit 1;\
	fi

dist-rpm-sign: dist-rpm
	@if [ "${RPM}" != '' ]; then\
	  cp redhat/rpm* dist;\
	  cd dist;\
	  ${RPM} --rcfile rpmrc --addsign `echo ${DISTRPM} | \
	    sed 's+dist/++g'`;\
	  ${RM} -rf rpmbuild;\
	  ${RM} -f rpm*;\
	else\
	  echo "Cannot sign RPM packages: required tool rpm is not available";\
	  exit 1;\
	fi

dist-deb: ${DISTDEB}

%_${VERSION}.orig.tar.gz %_${DEBVER}.diff.gz %_${DEBVER}.dsc \
   %_${DEBVER}_${DEBARCH}.deb: %-${VERSION}.tar.gz
	@if [ "${DEBUILD}" != '' -a -d debian ]; then\
	  cp ${DISTTGZ} dist/${PKGNAME}_${VERSION}.orig.tar.gz;\
	  zcat ${DISTTGZ} | (cd dist && tar -xf -);\
	  mkdir -p dist/${DISTDIR}/debian;\
	  (cd debian && tar cf - --exclude=CVS . \
	    | (cd ../dist/${DISTDIR}/debian && tar xBf -));\
	  (cd dist/${DISTDIR} && \
	      ${DEBUILD} -i -us -uc -sa -S && \
	      ${DEBUILD} -i -us -uc -b);\
	  ${RM} -rf dist/${DISTDIR};\
	else\
	  echo "Cannot build .deb packages";\
	  exit 1;\
	fi

dist-deb-sign: dist-deb
	@if [ "${DEBSIGN}" != '' -a "${DEBSIGS}" != '' ]; then\
	  ${DEBSIGN} -k4EB5E2C9 dist/${DEBBASE}_source.changes;\
	  ${DEBSIGN} -k4EB5E2C9 dist/${DEBBASE}_${DEBARCH}.changes;\
	  ${DEBSIGS} --sign=gpg --default-key=osspkg@gmail.com\
	    dist/${DEBBASE}_${DEBARCH}.deb;\
	else\
	  echo "Cannot sign .deb packages: required tools debsign and debsigs are not available";\
	  exit 1;\
	fi


# DO NOT DELETE THIS LINE -- make depend depends on it.

treex.o:  treex.h
parsex.o:  parsex.h
debug.o:   debug.h
debug.o:  treex.h
find.o: find.h 
find.o:  treex.h debug.h
