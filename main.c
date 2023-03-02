/*
Program CPU Usage Monitor
Main
Author: Damian Lech
*/

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include "getCpuInfo.h"

#include "obtainCpuStatistics.h"

#include "calculations.h"

int main()
{
    int **cpuCoresAsMatrix;

    int numberOfCpus = getNumberOfCpus();

    int numberOfStatistics = getnumberOfStatistics();

    //cpuCoresAsMatrix = getDataFromFile(numberOfCpus, numberOfStatistics);

    while ( 0 == 0)
        calculateCpuUsage(getDataFromFile(numberOfCpus, numberOfStatistics));

    //printf("%d", cpuCoresAsMatrix[0][0]);

    for (int i = 0; i < numberOfCpus; i++)
    {
        free(cpuCoresAsMatrix[i]);
    }

    free(cpuCoresAsMatrix);
}

