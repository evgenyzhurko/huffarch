#!/bin/sh
[ -f Makefile ] && make clean
rm -f src/Makefile
rm -f Makefile
rm -f Makefile.in
rm -f aclocal.m4
rm -rf autom4te.cache
rm -f config.guess
rm -f config.h
rm -f config.h.in
rm -f config.log
rm -f config.status
rm -f config.sub
rm -f configure
rm -f compile
rm -f depcomp
rm -f install-sh
rm -f missing
rm -f mkinstalldirs
rm -f stamp-h1
rm -f src/Makefile.in