#include <pthread.h>

#include <semaphore.h>

#include "varCreate.h"

#include "threadFunctions.h"

void varCreate()
{
    pthread_mutex_init(&mutexCheckReadData, NULL);

    pthread_mutex_init(&mutexWatchdog, NULL);

    pthread_cond_init(&condReader, NULL);

    pthread_cond_init(&condAnalyzer, NULL);

    pthread_cond_init(&condPrinter, NULL);

    sem_init(&semReaderEmpty, 0, 1);

    sem_init(&semReaderFull, 0, 0);

    sem_init(&semAnalyzerEmpty, 0, 1);

    sem_init(&semAnalyzerFull, 0, 0);
}
