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
 

E=`./metrics/halstead/effortToImplement.sh $1 $2`

calc="define int(number) {
   auto oldscale
   oldscale = scale
   scale = 0
   number /= 1
   scale = oldscale
   return number
}

define power(number,exponent) {
   if (exponent == int(exponent)) {
      return number ^ exponent 
   } else {
      return e( exponent * l(number) )
   }
}

power("$E",2/3)/3000
"

echo $E
B=`echo $calc | bc -l`
B=${B/%.*/}

echo $B