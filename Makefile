Run: main.o getCpuInfo.o obtainCpuStatistics.o
	gcc main.o getCpuInfo.o obtainCpuStatistics.o -o Run

main.o: main.c
	gcc -c -Wall -Wextra main.c

getCpuInfo.o: getCpuInfo.c getCpuInfo.h
	gcc -c -Wall -Wextra getCpuInfo.c

obtainCpuStatistics.o: obtainCpuStatistics.c obtainCpuStatistics.h
	gcc -c -Wall -Wextra obtainCpuStatistics.c

clean:
	rm *.o
