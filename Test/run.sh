#!/usr/bin/env bash

try-clear () {
	if [ -n "$CLEAR" ]; then
		clear
	fi
}
echo "#include \"./Data/$1.c\"" > image.tmp.c
cat image.c | awk '{if (NR > 1) print}' >> image.tmp.c
gcc -lm image.tmp.c ../SmartCarProgram01/code/image.c -o image.tmp.out && try-clear && ./image.tmp.out
echo [$1]
