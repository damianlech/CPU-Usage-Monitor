CC = gcc

CFLAGS = -c -Wall -Wextra

Run: main.o getCpuInfo.o obtainCpuStatistics.o calculations.o
	$(CC) main.o getCpuInfo.o obtainCpuStatistics.o calculations.o -o Run

tests.o: getCpuInfo.o obtainCpuStatistics.o
	$(CC) tests.c getCpuInfo.o obtainCpuStatistics.o -o test

main.o: main.c
	$(CC) $(CFLAGS) main.c

getCpuInfo.o: getCpuInfo.c getCpuInfo.h
	$(CC) $(CFLAGS) getCpuInfo.c

obtainCpuStatistics.o: obtainCpuStatistics.c obtainCpuStatistics.h
	$(CC) $(CFLAGS) obtainCpuStatistics.c

calculations.o: calculations.c calculations.h
	$(CC) $(CFLAGS) calculations.c

test: tests.o
	./test

clean:
	rm *.o
