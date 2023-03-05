/*
Program CPU Usage Monitor
Main
Author: Damian Lech
*/

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <pthread.h>

#include <signal.h>

#include <semaphore.h>

#include "getCpuInfo.h"

#include "obtainCpuStatistics.h"

#include "calculations.h"

#include "threadFunctions.h"



void signalCheck()
{
    signalChecker = 1;
    printf("\nExiting program...\n");
}

int main()
{

    //signal checks
    signal(SIGINT, signalCheck);
    //signal(SIGTERM, signalCheck);

    //initialize mutex and semaphores
    pthread_mutex_init(&mutexCheckReadData, NULL);

    sem_init(&semEmpty, 0, 1);

    sem_init(&semFull, 0, 0);

    //initialize cpu info
    getNumberOfCpus();

    getnumberOfStatistics();

    //create threads
    pthread_t Reader;

    pthread_t Analyzer;

    pthread_t Printer;

    //start threads TODO
    pthread_create(&Reader, NULL, (void*)&runReader, NULL);

    pthread_create(&Analyzer, NULL, (void*)&runAnalyzer, NULL);

    pthread_create(&Printer, NULL, (void*)&runAnalyzer, NULL);

    //join threads to free up memory
    pthread_join(Reader, NULL);

    pthread_join(Analyzer, NULL);

    //destroy mutex and semaphores
    pthread_mutex_destroy(&mutexCheckReadData);

    sem_destroy(&semEmpty);

    sem_destroy(&semFull);

    //free up memory allocated to matrix
    for (int i = 0; i < numberOfCpus; i++)
    {
        free(cpuCoresAsMatrix[i]);
    }

    free(cpuCoresAsMatrix);

    for (int i = 0; i < numberOfCpus; i++)
    {
        free(cpuCoresAsMatrixOld[i]);
    }

    free(cpuCoresAsMatrixOld);

    return 0;
}

