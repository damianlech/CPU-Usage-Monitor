#ifndef READATA_H

#define READATA_H

/*
- getNumberOfCpus will read the file searching for strings starting with "cpu", count them and return the value
- getNumberOfStatistics will read the first string and based on the number of " " characters, return the number of statistics
- getDataFromFile will return a matrix (pointer to a pointer) with all statistics based on number of cpus and statistics inside of /proc/stat
*/

int getNumberOfCpus();

int getnumberOfStatistics();

int **getDataFromFile(int numberOfCpus, int numberOfStatistics);

#endif // READATA_H
