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

    //initialize mutex and conditional variables
    pthread_mutex_init(&mutexBuffer, NULL);

    pthread_cond_init(&matrixCreatedCondition, NULL);

    //initialize cpu info
    getNumberOfCpus();

    getnumberOfStatistics();

    //create threads
    pthread_t Reader;

    pthread_t Analyzer;

    //start threads TODO
    pthread_create(&Reader, NULL, (void*)&runReader, NULL);

    pthread_create(&Analyzer, NULL, (void*)&runAnalyzer, NULL);

    //join threads to free up memory
    pthread_join(Reader, NULL);

    pthread_join(Analyzer, NULL);

    //destroy mutex and conditional variables
    pthread_mutex_destroy(&mutexBuffer);

    pthread_cond_destroy(&matrixCreatedCondition);

    return 0;
}

