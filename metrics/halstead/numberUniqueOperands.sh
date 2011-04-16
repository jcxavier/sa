#!/bin/bash
#
# author: João Xavier
# date: 16/04/2011
#
# metric: Number of Unique Operands
# language: C, C++
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi

SRCCODE=$1
XMLDUMP=$2


IDENTIFIERCOUNT=`grep '<Var \|<Field ' -c $XMLDUMP`      # identifiers

TYPESPECLIST=( 'bool' 'char' 'double' 'float' 'int' 'long' 'short' 'signed' 'unsigned' 'void' )
TYPESPECCOUNT=0

for TYPESPEC in ${TYPESPECLIST[*]}; do
    if [ `grep -w $TYPESPEC $SRCCODE -c` -gt 0 ]; then
        let TYPESPECCOUNT=$TYPESPECCOUNT+1
    fi  
done

LITERALCOUNT=0
LITLIST=`grep '<IntegerLiteral \|<CharacterLiteral \|<StringLiteral ' $XMLDUMP | awk '{
print substr($6, 8, length($6) - 10) }'`

for LITITEM in $LITLIST; do
    eval "LITHASH""$LITITEM"='1'
done

for h in ${!LITHASH*}; do
    let LITERALCOUNT=$LITERALCOUNT+1
done

# floating literals

TMPFILE="____TMP_FILE__"
sed -e 's/[^0-9. ]*//g' -e  's/ \+/ /g' $SRCCODE | tr ' ' '\n' | grep '[0-9]*\.[0-9+]' | sed 's/ //g' > $TMPFILE"_"
sort -u $TMPFILE"_" > $TMPFILE

FLOATLITCOUNT=`grep '.' $TMPFILE -c`
rm -f $TMPFILE*

let LITERALCOUNT=$LITERALCOUNT+$FLOATLITCOUNT

let NUOPERANDS=$IDENTIFIERCOUNT+$TYPESPECCOUNT+$LITERALCOUNT
echo $NUOPERANDS
