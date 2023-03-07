#include <pthread.h>

#include <semaphore.h>

#include <stdio.h>

#include "varInitDestroy.h"

#include "threadFunctions.h"

//initialize all mutexes, conditional variables and seaphores
void varInit()
{
    pthread_mutex_init(&mutexCheckReadData, NULL);

    pthread_mutex_init(&mutexWatchdog, NULL);

    pthread_cond_init(&condWatchdog, NULL);

    pthread_mutex_init(&mutexLogger, NULL);

    pthread_cond_init(&condLogger, NULL);

    sem_init(&semReaderEmpty, 0, 1);

    sem_init(&semReaderFull, 0, 0);

    sem_init(&semAnalyzerEmpty, 0, 1);

    sem_init(&semAnalyzerFull, 0, 0);
}

//destroy all mutexes, conditional variables and seaphores
void varDestroy()
{
    pthread_mutex_destroy(&mutexCheckReadData);

    pthread_mutex_destroy(&mutexWatchdog);

    pthread_cond_destroy(&condWatchdog);

    pthread_mutex_destroy(&mutexLogger);

    pthread_cond_destroy(&condLogger);

    sem_destroy(&semReaderEmpty);

    sem_destroy(&semReaderFull);

    sem_destroy(&semAnalyzerEmpty);

    sem_destroy(&semAnalyzerFull);
}
