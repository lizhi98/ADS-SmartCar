#!/usr/bin/env bash

try-clear () {
	if [ -n "$CLEAR" ]; then
		clear
	fi
}
echo "#include \"./Data/$1.c\"" > image.tmp.c
cat image.c | awk '{if (NR > 1) print}' >> image.tmp.c
if [[ -z "$DEBUG" ]]; then
	gcc -lm image.tmp.c ../SmartCarProgram01/code/image.c -o image.tmp.out && try-clear && ./image.tmp.out
else
	gcc -lm image.tmp.c ../SmartCarProgram01/code/image.c -g -o image.tmp.out && try-clear && gdb ./image.tmp.out
fi
if [[ $? != 0 ]]; then
	echo [$1 ERROR]
	exit 1
fi
echo [$1]
