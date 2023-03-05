#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

#include "calculations.h"

//mutex and semaphores defined
pthread_mutex_t mutexCheckReadData;

sem_t semEmpty;

sem_t semFull;

int signalChecker = 0;

//Run getDataFromFile every second and update the matrix with information
void* runReader()
{
    //alloc matrixes
    cpuCoresAsMatrix = malloc(numberOfCpus * sizeof(int *));

    for (int i = 0; i < numberOfCpus; i++)
    {
        cpuCoresAsMatrix[i] = malloc(numberOfStatistics * sizeof(int));
    }

    cpuCoresAsMatrixOld = malloc(numberOfCpus * sizeof(int *));

    for (int i = 0; i < numberOfCpus; i++)
    {
        cpuCoresAsMatrixOld[i] = malloc(numberOfStatistics * sizeof(int));
    }

    //run until signal detected
    while(signalChecker == 0)
    {
        //wait for semaphore
        sem_wait(&semEmpty);

        pthread_mutex_lock(&mutexCheckReadData);

        //write old data to the matrix
        getOldDataFromFile();

        if (signalChecker == 0)
            sleep(1);
        //write current data to the matrix
        getDataFromFile();

        pthread_mutex_unlock(&mutexCheckReadData);

        //post semaphore
        sem_post(&semFull);
    }
    return 0;
}

//calculates CPU usage percentage
void* runAnalyzer()
{
    //allocate memory for CPU_percentage
    CPU_Percentage = malloc(numberOfCpus * sizeof(int));

    //run until signal detected
    while(signalChecker == 0)
    {
        sem_wait(&semFull);

        pthread_mutex_lock(&mutexCheckReadData);

        //Run calculate function
        if (signalChecker == 0)
            calculateCpuUsage();

        pthread_mutex_unlock(&mutexCheckReadData);

        sem_post(&semEmpty);
    }
    //free up memory allocated to CPU_Percentage
    free(CPU_Percentage);

    return 0;
}
