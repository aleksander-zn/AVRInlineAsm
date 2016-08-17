#!/bin/bash -x
cat 01.c
[ -f 01.o ] && rm 01.o
[ -f 01.lst ] && rm 01.lst
avr-gcc -mmcu=atmega328p -Os -Wall -g 01.c -c -o 01.o
if [ -f 01.o ]
then
	avr-objdump -xS 01.o > 01.lst
	rm 01.o
	cat 01.lst
fi
