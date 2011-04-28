#!/bin/bash
#
# author: João Xavier
# date: 20/04/2011
#
# metric: Program Line Size
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "usage: "$ME" <source code file> [max line size (defaults to 78)]"
    exit
fi

SRCCODE=$1
MAXSIZE='78'

if [ $# -eq 2 ]; then
    MAXSIZE=$2
fi

TMPFILE="____"$SRCCODE

grep . $SRCCODE | awk '{ if (length($0) > '$MAXSIZE') print 1 }' > $TMPFILE

LINECOUNT=`grep . $TMPFILE -c`
rm -f $TMPFILE

echo $LINECOUNT
