#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

//Create a dynamically allocated 2D matrix
int **cpuCoresAsMatrix;

//create a dynamically allocated 2D matrix and fill it with statistics using tokens
int **getDataFromFile()
{
    //allocate memory for the matrix
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

            //printf("%d ", cpuCoresAsMatrix[i][j]);
        }
    }

    fclose(filePointer);

    //printf("%d ", cpuCoresAsMatrix[2][4]);

    return cpuCoresAsMatrix;
}
