CC = gcc

CFLAGS = -c -Wall -Wextra

BINARIES = main.o getCpuInfo.o obtainCpuStatistics.o calculations.o threadFunctions.o varCreate.o varDestroy.o

Run: $(BINARIES)
	$(CC) $(BINARIES) -o Run

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

threadFunctions.o: threadFunctions.c threadFunctions.h
	$(CC) $(CFLAGS) threadFunctions.c

varCreate.o: varCreate.c varCreate.h
	$(CC) $(CFLAGS) varCreate.c

varDestroy.o: varDestroy.c varDestroy.h
	$(CC) $(CFLAGS) varDestroy.c

test: tests.o
	./test

clean:
	rm *.o
