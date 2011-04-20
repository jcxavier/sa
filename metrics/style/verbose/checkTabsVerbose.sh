#!/bin/bash
#
# author: João Xavier
# date: 20/04/2011
#
# metric: Check if Tabs Exist (Verbose)
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 1 ]; then
    echo "usage: "$ME" <source code file>"
    exit
fi

awk '/\t/' $1
