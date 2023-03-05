CC = gcc

CFLAGS = -c -Wall -Wextra -std=c99

#CLANGFLAGS -Wno-declaration-after-statement to disable "mixing declarations and code is incompatible with standards before C99" since the code is supposed to be C99 and later compatible anyway
#-c -Weverything -std=c99 -Wno-declaration-after-statement

BINARIES = main.o getCpuInfo.o obtainCpuStatistics.o calculations.o threadFunctions.o varInitDestroy.o

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

varInitDestroy.o: varInitDestroy.c varInitDestroy.h
	$(CC) $(CFLAGS) varInitDestroy.c

test: tests.o
	./test

clean:
	rm *.o
