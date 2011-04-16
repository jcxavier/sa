#!/bin/bash
#
# author: João Xavier
# date: 16/04/2011
#
# metric: Program Volume
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi
 

N=`./metrics/halstead/programLength.sh $1 $2`
n=`./metrics/halstead/vocabularySize.sh $1 $2`

calc=$N"*l("$n")/l(2)"

V=`echo $calc | bc -l`
V=${V/%.*/}

echo $V