#!/bin/bash
#
# author: João Xavier
# date: 16/04/2011
#
# metric: Effort to Implement
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi
 

V=`./metrics/halstead/programVolume.sh $1 $2`
D=`./metrics/halstead/difficultyLevel.sh $1 $2`

let E=$V*$D
echo $E