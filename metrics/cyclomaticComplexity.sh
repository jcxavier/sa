#!/bin/bash
#
# author: João Xavier
# date: 20/04/2011
#
# metric: McCabe's Cyclomatic Complexity
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 1 ]; then
    echo "usage: "$ME" <xml dump file>"
    exit
fi

XMLDUMP=$1


CONDCOUNT=`grep '<IfStmt \|<ConditionalOperator \|<CaseStmt ' -c $XMLDUMP`
LOOPCOUNT=`grep '<WhileStmt \|<ForStmt \|<DoStmt ' -c $XMLDUMP`
LOGICALCOUNT=`grep ' kind="land">\| kind="lor">' -c $XMLDUMP`

let CC=$CONDCOUNT+$LOOPCOUNT+$LOGICALCOUNT+1
echo $CC
