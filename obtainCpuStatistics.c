#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

//Create a dynamically allocated 2D matrix
int **cpuCoresAsMatrix;

int **cpuCoresAsMatrixOld;

//create a dynamically allocated 2D matrix and fill it with statistics using tokens
void getDataFromFile()
{
    //allocate memory for the matrix
    //sleep(1);
        //cpuCoresAsMatrixOld = cpuCoresAsMatrix;



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
        }
    }

    fclose(filePointer);
}

void getOldDataFromFile()
{
    //allocate memory for the matrix
    //sleep(1);
        //cpuCoresAsMatrixOld = cpuCoresAsMatrix;



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

            cpuCoresAsMatrixOld[i][j] = atoi(token);
        }
    }

    fclose(filePointer);
}
