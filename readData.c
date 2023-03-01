#include "readData.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char singleLine[100];

FILE * filePointer;

//Get information on the number of cpus for program to read
int getNumberOfCpus()
{
    int numberOfCpus;

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
    int numberOfStatistics;

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

//create a dynamically allocated 2D matrix and fill it with statistics using tokens
int **getDataFromFile(int numberOfCpus, int numberOfStatistics)
{
    //Create a dynamically allocated 2D matrix
    int **cpuCoresAsMatrix;

    cpuCoresAsMatrix = malloc(numberOfCpus * sizeof(int *));

    for (int i = 0; i < numberOfCpus; i++)
    {
        cpuCoresAsMatrix[i] = malloc(numberOfStatistics * sizeof(int));
    }

    filePointer = fopen("/proc/stat", "r");

    //start writing variables to the matrix
    for (int i = 0; i < numberOfCpus; i++)
    {
        fgets(singleLine, 100, filePointer);

        //set the " " character to be omitted by the token maker
        const char toRemove[2] = " ";

        char *token;

        //create first token, "cpu"
        token = strtok(singleLine, toRemove);

        //create tokens from the rest of the string and write them into a matrix
        for (int j = 0; j < numberOfStatistics; j++)
        {
            token = strtok(NULL, toRemove);

            cpuCoresAsMatrix[i][j] = atoi(token);

            printf("%d ", cpuCoresAsMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n");

    fclose(filePointer);

    return cpuCoresAsMatrix;
}
