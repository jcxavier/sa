#!/bin/bash
#
# author: João Xavier
# date: 17/04/2011
#
# metric: Lines of Code
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 1 ]; then
    echo "usage: "$ME" <source code file>"
    exit
fi

echo `grep '[^ ]' $1 -c`
