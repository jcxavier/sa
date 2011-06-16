#!/bin/bash
#
# author: João Xavier
# date: 20/04/2011
#
# metric: Space Between Parentheses and Brackets
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 1 ]; then
    echo "usage: "$ME" <source code file>"
    exit
fi

SRCCODE=$1

SPACES=`grep '){' $SRCCODE -c`

if [ $SPACES -gt 0 ]; then
    SPACES=1
fi

echo $SPACES
