Run: main.o
	gcc main.o -o Run

main.o: main.c
	gcc -c -Wall -Wextra main.c
