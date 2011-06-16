#!/bin/bash
#
# author: João Xavier
# date: 15/04/2011
#
# metric: Total Number of Operators
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi

SRCCODE=$1
XMLDUMP=$2

SCSPEC=`grep -w 'static\|typedef\|virtual\|mutable\|const\|\friend\|volatile'\
 -c $SRCCODE`   # type/storage reserved words

RESERVED=`grep -w 'asm\|break\|case\|class\|continue\|default\|delete\|do\|else\|\
enum\|for\|goto\|if\|new\|operator\|private\|protected\|public\|return\|sizeof\|struct\|switch\|\
this\|union\|while\|namespace\|using\|try\|catch\|throw\|const_cast\|static_cast\|dynamic_cast\|\
reinterpret_cast\|typeid\|template\|explicit\|true\|false\|typename'\
 -c $SRCCODE`   # reserved words

OPERATOR=`grep '<DeclStmt \|<BinaryOperator \|<UnaryOperator \|<ConditionalOperator \|<ArraySubscriptExpr \|\
<CompoundStmt \|name="operator&.t;&.t;"'\
 -c $XMLDUMP`    # all operators

let TNOPERATORS=$SCSPEC+$RESERVED+$OPERATOR
echo $TNOPERATORS
