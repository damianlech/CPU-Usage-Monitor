#include <pthread.h>

#include <semaphore.h>

#include "varInitDestroy.h"

#include "threadFunctions.h"

void varInit()
{
    pthread_mutex_init(&mutexCheckReadData, NULL);

    pthread_mutex_init(&mutexWatchdog, NULL);

    pthread_cond_init(&condWatchdog, NULL);

    sem_init(&semReaderEmpty, 0, 1);

    sem_init(&semReaderFull, 0, 0);

    sem_init(&semAnalyzerEmpty, 0, 1);

    sem_init(&semAnalyzerFull, 0, 0);
}


void varDestroy()
{
    pthread_mutex_destroy(&mutexCheckReadData);

    pthread_mutex_destroy(&mutexWatchdog);

    pthread_cond_destroy(&condWatchdog);

    sem_destroy(&semReaderEmpty);

    sem_destroy(&semReaderFull);

    sem_destroy(&semAnalyzerEmpty);

    sem_destroy(&semAnalyzerFull);
}
