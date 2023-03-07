# CPUUsageMonitor
Multithreaded program designed to read /proc/stat information and print out average cpu usage.
There are 5 threads in total:
1. Reader - reads the /proc/stat file
2. Analyzer - converts the data into the averge cpu usage
3. Printer - prints out the value to the console
4. Watchdog - if one of the above threads takes at least 2 seconds to complete, quits the program
5. Logger - Saves information from oter threads into a log file


Optimized for gcc with -Wall and -Wextra as well as clang with -Weverything
