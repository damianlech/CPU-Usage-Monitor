#ifndef GETCPUINFO_H

#define GETCPUINFO_H

//Getting information about CPU cores and the number of statistics saved in the /proc/stat file

extern char singleLine[100];

extern FILE *filePointer;

extern int numberOfCpus;

extern int numberOfStatistics;

int getNumberOfCpus();

int getnumberOfStatistics();

#endif // GETCPUINFO_H
