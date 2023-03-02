#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include"getCpuInfo.h"

#include "calculations.h"

//int numberOfCpus;

//int numberOfStatistics;

//int **cpuCoresAsMatrix;

int calculateCpuUsage(int **dataFromFile)
{
    //int cpuUsage[3];

    int currentStatistics[3][10];

    int prevStatistics[3][10];

    for (int i = 0; i < 3; i++)
        memcpy(&currentStatistics[i], dataFromFile[i], sizeof(currentStatistics));

    int x = dataFromFile[0][0];

    //currentStatistics = dataFromFile;

    for (int i = 0; i < 3; i++)
        memcpy(prevStatistics[i], currentStatistics[i], sizeof(dataFromFile));

    int y = x;

    sleep(1);

    //prevStatistics = currentStatistics;

    for (int i = 0; i < 3; i++)
        memcpy(&currentStatistics[i], dataFromFile[i], sizeof(dataFromFile));

    x = dataFromFile[0][0];

    //currentStatistics = dataFromFile;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", dataFromFile[i][j]);
        }
        printf("\n%d\n", (int)sizeof(dataFromFile));
    }

    printf("\n\n\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", prevStatistics[i][j]);
        }
        printf("\n");
    }


    printf("\n\n\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", currentStatistics[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n%d, %d\n", x, y);

    return 0;
}
