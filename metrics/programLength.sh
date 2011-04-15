#!/bin/bash
#
# author: João Xavier
# date: 15/04/2011
#
# metric: Program Length
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi

TNOPERANDS=`./metrics/totalNumberOperands.sh $1 $2`
TNOPERATORS=`./metrics/totalNumberOperators.sh $1 $2`
let PL=$TNOPERANDS+$TNOPERATORS
echo $PL