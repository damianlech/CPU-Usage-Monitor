#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "getCpuInfo.h"

char singleLine[100];

FILE *filePointer;

int numberOfCpus;

int numberOfStatistics;

//Get information on the number of cpus for program to read
int getNumberOfCpus()
{
    filePointer = fopen("/proc/stat", "r");

    //search how many lines start with "cpu" and increase counter but this much
    int counter = 0;

    while(!feof(filePointer))
    {
        fgets(singleLine, 100, filePointer);

        if (singleLine[0] == 'c' && singleLine[1] == 'p' && singleLine [2] == 'u')
        {
            counter++;
        }
    }

    //update the number of cpus with counter
    numberOfCpus = counter;

    fclose(filePointer);

    return(numberOfCpus);
}

//Get information on the number of statistics for program to read
int getnumberOfStatistics()
{
    filePointer = fopen("/proc/stat", "r");

    //get the number of ' ' characters in the first line, since the first line always starts with "cpu  " - the number of spaces - 1 will equal the number of statistics
    fgets(singleLine, 100, filePointer);

    int numberOfSpaces = 0;

    for (int i = 0; i < (int)strlen(singleLine); i++)
    {
        if (singleLine[i] == ' ')
        {
            numberOfSpaces++;
        }
    }

    //update the number of statistics with the number of spaces
    numberOfStatistics = numberOfSpaces - 1;

    fclose(filePointer);

    return(numberOfStatistics);
}
