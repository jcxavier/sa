#!/bin/bash
#
# author: João Xavier
# date: 14/04/2011
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit
fi

SRCCODE=$1;
SRCCODENOCMT="_nc_"$SRCCODE
SRCXML=${SRCCODE/%.c*/.xml}

clang -cc1 $SRCCODE -ast-print-xml
FXX=`grep $SRCCODE $SRCXML | awk '{ gsub(/id=/, ""); print $2 }'`
rm -f $2
echo "<AST>" >> $2
echo -e "\n\t<SourceCodeFile> "$1" </SourceCodeFile>\n" >> $2
eval "xgrep -x '//TranslationUnit/*[@file="$FXX"]' $SRCXML >> $2"
echo -e "\n</AST>" >> $2
rm $SRCXML
./rmcomments.sed < $SRCCODE > $SRCCODENOCMT