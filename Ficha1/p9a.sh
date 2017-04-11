#!/bin/bash

if [ $# -ne 1 ]
then
	echo "`basename $0`: invalid number of arguments"
	exit 1
fi

FILE=$1

if [ ! -f "$FILE.c" ]
then
	echo "`basename $FILE.c`: file does not exist"
	exit 1
fi

rm --force $FILE
rm --force $FILE.o

gcc -O3 -Wall -o $FILE $FILE.c

chmod +x $p9a

./$FILE

