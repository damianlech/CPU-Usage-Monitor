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

#include "varInitDestroy.h"

int main()
{
    //signal checks
    signal(SIGINT, signalCheck);
    signal(SIGTERM, signalCheck);

    //initialize mutex and semaphores
    varInit();

    //initialize cpu info
    getNumberOfCpus();

    getnumberOfStatistics();

    //create threads
    pthread_t Reader;

    pthread_t Analyzer;

    pthread_t Printer;

    pthread_t Watchdog;

    pthread_t Logger;

    //start threads
    pthread_create(&Reader, NULL, runReader, NULL);

    pthread_create(&Analyzer, NULL, runAnalyzer, NULL);

    pthread_create(&Printer, NULL, runPrinter, NULL);

    pthread_create(&Watchdog, NULL, runWatchdog, NULL);

    pthread_create(&Logger, NULL, runLogger, NULL);

    //join threads to free up memory
    pthread_join(Reader, NULL);

    pthread_join(Analyzer, NULL);

    pthread_join(Printer, NULL);

    pthread_join(Watchdog, NULL);

    pthread_join(Logger, NULL);

    //destroy mutex and semaphores
    varDestroy();

    return 0;
}

