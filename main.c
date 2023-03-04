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
    i++;
    printf("\nExiting program...\n");
}

int main()
{
    //signal checks
    signal(SIGINT, signalCheck);
    //signal(SIGTERM, signalCheck);

    pthread_mutex_init(&mutexBuffer, NULL);

    pthread_cond_init(&matrixCreatedCondition, NULL);



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
    {

    }


    //sleep(1);

    //pthread_mutex_unlock(&mutexBuffer);

    //join threads to free up memory
    //pthread_exit(NULL);



    pthread_join(Reader, NULL);

    pthread_join(Analyzer, NULL);

    //pthread_exit(NULL);

    pthread_mutex_destroy(&mutexBuffer);

    pthread_cond_destroy(&matrixCreatedCondition);




    return 0;
}

