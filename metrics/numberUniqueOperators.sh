#!/bin/bash
#
# author: João Xavier
# date: 15/04/2011
#
# metric: Number of Unique Operators
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi

SRCCODE=$1
XMLDUMP=$2

SCSPECWORDS=( auto extern inline register static typedef virtual mutable const friend volatile )
SCSPECCOUNT=0

for WORD in ${SCSPECWORDS[*]}; do
    if [ `grep -w $WORD $SRCCODE -c` -gt 0 ]; then
        let SCSPECCOUNT=$SPSPECCOUNT+1
    fi  
done

RESERVEDWORDS=( asm break case class continue default delete do else enum for goto if new operator 
private protected public return sizeof struct switch this union while namespace using try catch 
throw const_cast static_cast dynamic_cast reinterpret_cast typeid template explicit true false typename )
RESERVEDCOUNT=0

for WORD in ${RESERVEDWORDS[*]}; do
    if [ `grep -w $WORD $SRCCODE -c` -gt 0 ]; then
        let RESERVEDCOUNT=$RESERVEDCOUNT+1
    fi  
done

OPERATORCOUNT=0
    
let NUOPERATORS=$SCSPECCOUNT+$RESERVEDCOUNT+$OPERATORCOUNT    
echo $NUOPERATORS    
    



#OPERATOR=`grep '<BinaryOperator \|<UnaryOperator \|<ConditionalOperator \|<ArraySubscriptExpr \|\
#<CompoundStmt \|name="operator&.t;&.t;"'\
# -c $XMLDUMP`    # all operators

#let TNOPERATORS=$SCSPEC+$RESERVED+$OPERATOR
#echo $TNOPERATORS
