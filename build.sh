#!/bin/bash
brew install coreutils gnu-sed figlet
export PATH="/usr/local/opt/gnu-sed/libexec/gnubin:$PATH"

pw=`pwd`
sed '/\/\/MAXXX/ i\#define MAX_FILE "'$pw'/.max.txt"' Hangman.c > tmp.c
mv tmp.c Hangman.c
sed '/\/\/DEFINE/ i\#define DEF "'$pw'/cities.txt"' Select.h > tmp.h
mv tmp.h Select.h
sed '/\/\/DEFINE/ i\#define city "'$pw'/cities.txt"' Select.h> tmp.h
mv tmp.h Select.h
sh addlevel.sh word $pw/words.txt
sh addlevel.sh animal $pw/animals.txt


