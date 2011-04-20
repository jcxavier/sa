#!/bin/bash
#
# author: João Xavier
# date: 20/04/2011
#
# metric: Block Brackets in a Single Line
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 1 ]; then
    echo "usage: "$ME" <source code file>"
    exit
fi

SRCCODE=$1

BLKBRACKETS=`grep -e '{.*}' -c $SRCODE`

if [ $BLKBRACKETS -gt 0 ]; then
    BLKBRACKETS=1
fi

echo $BLKBRACKETS
