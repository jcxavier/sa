#!/bin/bash
#
# author: João Xavier
# date: 14/04/2011
#

ME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

if [ $# -ne 2 ]; then
    echo "usage: "$ME" <source code file> <xml dump file>"
    exit 1
fi

# Absolute path this script is in
SCRIPTPATH=`dirname $0`
RMCOMMENTS=$SCRIPTPATH'/rmcomments.sed'

SRCCODE=$1;
SRCCODENOCMT="_nc_"$SRCCODE
SRCXML=${SRCCODE/%.c*/.xml}

EXT=`echo $SRCCODE | awk -F . '{print $NF}'`

if [[ "$EXT" != "c" && "$EXT" != "cpp" ]]; then
    echo "error: not a .c or .cpp extension"
    exit 1
fi

clang -cc1 $SRCCODE -ast-print-xml
EXITCODE=$?

# If code does not compile, exit with error
if [ $EXITCODE -ne 0 ]; then
    echo "error in clang: code did not compile"
    exit 1
fi

FXX=`grep $SRCCODE $SRCXML | awk '{ gsub(/id=/, ""); print $2 }'`
rm -f $2
echo "<AST>" >> $2
echo -e "\n\t<SourceCodeFile> "$1" </SourceCodeFile>\n" >> $2
eval "xgrep -x '//TranslationUnit/*[@file="$FXX"]' $SRCXML >> $2"
echo -e "\n</AST>" >> $2
rm $SRCXML
$RMCOMMENTS < $SRCCODE > $SRCCODENOCMT

exit 0
