#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include "obtainCpuStatistics.h"

//Run getDataFromFile every second and update the matrix with information
void* runReader()
{
    for(int i = 0; i < 1;i++)
    {
        getDataFromFile();

        sleep(1);
    }

    return 0;
}

//todo
void* runAnalyzer()
{
    for(int i = 0; i < 10;i++)
    {
        printf("%d\n\n", cpuCoresAsMatrix[0][0]);
    }

    return 0;
}
