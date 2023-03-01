#include "readData.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int numberOfCpus = 0; //number of lines in /proc/stat that starts with "cpu"

int numberOfStatistics = 0; // number of statistics in lines that start with "cpu"

char singleLine[100];

void getDataFromFile()
{
    //Create a FILE pointer and read /proc/stat
    FILE * filePointer;

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

    //close and open file to reset the !feof
    fclose(filePointer);

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

    //update the number of cpus with the number of spaces
    numberOfStatistics = numberOfSpaces - 1;

    //close and open file to reset the !feof
    fclose(filePointer);

    filePointer = fopen("/proc/stat", "r");

    //create a dynamic matrix to store all statistic about all cpus
    int cpuCoresAsMatrix[numberOfCpus][numberOfStatistics];

    //start writing variables to the matrix
    for (int i = 0; i < numberOfCpus; i++)
    {
        fgets(singleLine, 100, filePointer);

        //set the " " character to be omitted by the token maker
        const char toRemove[2] = " ";

        char *token;

        //create first token, "cpu"
        token = strtok(singleLine, toRemove);

        //create tokens from the rest of the string and write them into an integer matrix cpuCoresAsMatrix
        for (int j = 0; j < numberOfStatistics; j++)
        {
            token = strtok(NULL, toRemove);

            cpuCoresAsMatrix[i][j] = atoi(token);

            printf("%d ", cpuCoresAsMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n");

    //close the file for good
    fclose(filePointer);
}
