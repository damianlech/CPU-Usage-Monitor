Run: main.o readData.o
	gcc main.o readData.o -o Run

main.o: main.c
	gcc -c -Wall -Wextra main.c
	
readData.o: readData.c readData.h
	gcc -c -Wall -Wextra readData.c
	
clean:
	rm *.o
