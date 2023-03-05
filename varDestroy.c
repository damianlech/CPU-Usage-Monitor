#include <pthread.h>

#include <semaphore.h>

#include "varDestroy.h"

#include "threadFunctions.h"

void varDestroy()
{
    pthread_mutex_destroy(&mutexCheckReadData);

    pthread_mutex_destroy(&mutexWatchdog);

    pthread_cond_destroy(&condReader);

    pthread_cond_destroy(&condAnalyzer);

    pthread_cond_destroy(&condPrinter);

    sem_destroy(&semReaderEmpty);

    sem_destroy(&semReaderFull);

    sem_destroy(&semAnalyzerEmpty);

    sem_destroy(&semAnalyzerFull);
}
