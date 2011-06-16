#!/bin/bash
#
# author: João Xavier
# date: 15/04/2011
#
# metric: Total Number of Operands
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi

SRCCODE=$1
XMLDUMP=$2

IDENTIFIERS=`grep '<Var \|<Field \|<Record \|<Function \|<ParmVar ' -c $XMLDUMP`      # identifier declarations

ACCESS=`grep '<MemberExpr \|<DeclRefExpr ' -c $XMLDUMP` # variable calls

SIGNED=`grep -w 'unsigned\|signed' -c $SRCCODE`     # signed / unsigned
let TYPESPECS=$IDENTIFIERS+$SIGNED                  # sum with all declarations

LITERALS=`grep '<*Literal file=' -c $XMLDUMP`        # all literals except booleans (reserved words)

let TNOPERANDS=$IDENTIFIERS+$ACCESS+$TYPESPECS+$LITERALS
echo $TNOPERANDS
