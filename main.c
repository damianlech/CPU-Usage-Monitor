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
    i = 1;
}

int main()
{
    //signal checks
    //signal(SIGINT, signalCheck);

    signal(SIGTERM, signalCheck);

    //initialize cpu info
    getNumberOfCpus();

    getnumberOfStatistics();

    //create threads
    pthread_t Reader;

    pthread_t Analyzer;

    //create mutex
    //pthread_mutex_init(&mutexBuffer, NULL);

    //start threads TODO
    pthread_create(&Reader, NULL, (void*)&runReader, NULL);

    //sleep(2);

    pthread_create(&Analyzer, NULL, (void*)&runAnalyzer, NULL);


    while (i == 0)

    //join threads to free up memory
    pthread_join(Reader, NULL);

    pthread_join(Analyzer, NULL);

    pthread_mutex_destroy(&mutexBuffer);

    return 0;
}

