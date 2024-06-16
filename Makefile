all: main
main:
	gcc -o app -Wall -Werror src/main.c src/cw.c src/words.c
clear:
	rm app