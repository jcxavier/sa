#!/bin/bash
#
# author: João Xavier
# date: 16/04/2011
#
# metric: Time to Implement
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi
 

E=`./metrics/halstead/effortToImplement.sh $1 $2`

let T=$E/18
echo $T