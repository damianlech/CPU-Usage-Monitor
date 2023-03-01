CC = gcc

CFLAGS = -c -Wall -Wextra

Run: main.o getCpuInfo.o obtainCpuStatistics.o
	$(CC) main.o getCpuInfo.o obtainCpuStatistics.o -o Run

testgetCpuInfo.o: getCpuInfo.o
	$(CC) testgetCpuInfo.c getCpuInfo.o -o test

main.o: main.c
	$(CC) $(CFLAGS) main.c

getCpuInfo.o: getCpuInfo.c getCpuInfo.h
	$(CC) $(CFLAGS) getCpuInfo.c

obtainCpuStatistics.o: obtainCpuStatistics.c obtainCpuStatistics.h
	$(CC) $(CFLAGS) obtainCpuStatistics.c

test: testgetCpuInfo.o
	./test

clean:
	rm *.o
