#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

#include "calculations.h"

//mutex and conditional variable defined
pthread_mutex_t mutexCheckReadData;

//pthread_mutex_t mutexBuffer;

pthread_cond_t matrixCreatedCondition;

//pthread_cond_t startedAnalyzerCondition;

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
        printf("\n1\n");

        sem_wait(&semEmpty);

        pthread_mutex_lock(&mutexCheckReadData);

        //write old data to the matrix
        getOldDataFromFile();

        if (signalChecker == 0)
            sleep(1);
        //write current data to the matrix
        getDataFromFile();

        printf("\n3\n");

        pthread_mutex_unlock(&mutexCheckReadData);


        ///pthread_cond_signal(&matrixCreatedCondition);

        printf("\n6\n");

        sem_post(&semFull);

        //wait for Analyzer
        //pthread_cond_wait(&startedAnalyzerCondition, &mutexBuffer);

        printf("\n7\n");

    }

    //free up Analyzer
    pthread_cond_signal(&matrixCreatedCondition);

    return 0;
}

//todo
void* runAnalyzer()
{

    CPU_Percentage = malloc(numberOfCpus * sizeof(int));
    //run until signal detected
    while(signalChecker == 0)
    {
        printf("\n2\n");

        sem_wait(&semFull);

        pthread_mutex_lock(&mutexCheckReadData);

        printf("\n4\n");

        //pthread_cond_wait(&matrixCreatedCondition, &mutexCheckReadData);

        printf("\n5\n");

        //todo
        if (signalChecker == 0)
            calculateCpuUsage();

        pthread_mutex_unlock(&mutexCheckReadData);

        sem_post(&semEmpty);

    }
    free(CPU_Percentage);

    return 0;
}
