/*
Program CPU Usage Monitor
Main
Author: Damian Lech
*/

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <pthread.h>

#include "getCpuInfo.h"

#include "obtainCpuStatistics.h"

#include "calculations.h"

int **cpuCoresAsMatrix;

void* getIt()
{
    while(1)
        cpuCoresAsMatrix = getDataFromFile();
    //printf("%d\n\n", cpuCoresAsMatrix[2][4]);
    return 0;
}

void* Hello()
{
    printf("%d\n\n", cpuCoresAsMatrix[0][0]);
    sleep(1);
    return 0;
}

int main()
{
    //int **cpuCoresAsMatrix;

    getNumberOfCpus();

    getnumberOfStatistics();



    //int numberOfCpus = lCpuInfo.numberOfCpus;

    //int numberOfStatistics = lCpuInfo.numberOfStatistics;

    //cpuCoresAsMatrix = getDataFromFile();

    //while ( 0 == 0)
        //calculateCpuUsage(getDataFromFile(numberOfCpus, numberOfStatistics));

    //printf("%d", cpuCoresAsMatrix[0][0]);

    //for (int i = 0; i < numberOfCpus; i++)
    //{
        //free(cpuCoresAsMatrix[i]);
    //}

    //free(cpuCoresAsMatrix);

    pthread_t Reader;

    pthread_t Analyzer;

    while (1)
    {
        pthread_create(&Reader, NULL, (void*)&getDataFromFile, NULL);

        pthread_join(Reader, (void**) &cpuCoresAsMatrix);

        //printf("%d\n\n", cpuCoresAsMatrix[2][4]);
        fflush(stdout);

        pthread_create(&Analyzer, NULL, (void*)&Hello, NULL);


        //sleep(1);
    }

    pthread_exit(NULL);

    //printf("%d, %d", lCpuInfo.numberOfCpus, lCpuInfo.numberOfStatistics);
}

