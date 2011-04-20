#!/bin/bash
#
# author: João Xavier
# date: 20/04/2011
#
# metric: Space Between Brackets and Code (Verbose)
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 1 ]; then
    echo "usage: "$ME" <source code file>"
    exit
fi

grep '{.\+' -n $1
