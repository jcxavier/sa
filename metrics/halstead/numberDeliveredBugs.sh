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

calc="define int(number) {\n
\tauto oldscale\n
\toldscale = scale\n
\tscale = 0\n
\tnumber /= 1\n
\tscale = oldscale\n
\treturn number\n
}\n
\n
define power(number,exponent) {\n
\tif (exponent == int(exponent)) {\n
\t\treturn number ^ exponent\n 
\t} else {\n
\t\treturn e( exponent*l(number) )\n
\t}\n
}\n
\n
power("$E",2/3)/3000"

B=`echo -e $calc | bc -l`
echo "0"${B:0:7}