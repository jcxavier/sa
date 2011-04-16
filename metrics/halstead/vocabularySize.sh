#!/bin/bash
#
# author: João Xavier
# date: 16/04/2011
#
# metric: Vocabulary Size
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi
 

n1=`./metrics/halstead/numberUniqueOperators.sh $1 $2`
n2=`./metrics/halstead/numberUniqueOperands.sh $1 $2`

let n=$n1+$n2
echo $n