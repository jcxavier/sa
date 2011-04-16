#!/bin/bash
#
# author: João Xavier
# date: 16/04/2011
#
# metric: Program Level
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi
 

D=`./metrics/halstead/difficultyLevel.sh $1 $2`

calc="1/"$D

L=`echo $calc | bc -l`
echo "0"${L:0:7}