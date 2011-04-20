#!/bin/bash
#
# author: João Xavier
# date: 20/04/2011
#
# metric: Program Line Size
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <max line size>"
    exit
fi

SRCCODE=$1
MAXSIZE=$2
TMPFILE="____"$SRCCODE

grep . $SRCCODE | awk '{ if (length($0) > '$MAXSIZE') print 1 }' > $TMPFILE

LINECOUNT=`grep . $TMPFILE -c`
rm -f $TMPFILE

echo $LINECOUNT
