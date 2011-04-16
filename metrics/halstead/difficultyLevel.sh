#!/bin/bash
#
# author: João Xavier
# date: 16/04/2011
#
# metric: Difficulty Level
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi
 

N2=`./metrics/halstead/totalNumberOperands.sh $1 $2`
n1=`./metrics/halstead/numberUniqueOperators.sh $1 $2`
n2=`./metrics/halstead/numberUniqueOperands.sh $1 $2`

calc="("$n1"/2)*("$N2"/"$n2")"

D=`echo $calc | bc -l`
D=${D/%.*/}

echo $D