#!/bin/sh
if [ $# -eq 2 ];
then 
sed '/\/\/DEFINE/ i\#define '$1' "'$2'"' Select.h > test.h
sed -r 's/(\/\/CHANGE)([0-9]+)/echo "        if(strcmp(argv[1],-'$1')==0)\n            level=$((\2+1));\n\/\/CHANGE$((\2+1))"/ge' test.h > test2.h
sed '/        .*-'$1'.*/c\       else if(strcmp(argv[1],"-'$1'")==0)' test2.h > test3.h
sed -r 's/(\/\/SWITCH)([0-9]+)/echo "        case $((\2+1)):\n            c = strcat(cmd,'$1');\n           break;\n\/\/SWITCH$((\2+1))"/ge' test3.h > test4.h
sed -r 's/(#define MAX_LEVEL )([0-9]+)/echo "\1$((\2+1))"/ge' test4.h > Select.h
rm test*
gcc -Wall Hangman.c -o Hangman
echo "New level $1 is added to Hangman\n Usage ./Hangman -$1 \n"
else
echo "Syntax Error \n Usage ./addlevel.sh [flag] [path_to_word_list]\n"
fi



