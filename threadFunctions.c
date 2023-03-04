#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

#include "calculations.h"

//mutex and conditional variable defined
pthread_mutex_t mutexCheckReadData;

pthread_mutex_t mutexBuffer;

pthread_cond_t matrixCreatedCondition;

pthread_cond_t startedAnalyzerCondition;

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
        pthread_mutex_lock(&mutexCheckReadData);

        //write old data to the matrix
        getOldDataFromFile();

        if (signalChecker == 0)
            sleep(1);
        //write current data to the matrix
        getDataFromFile();

        pthread_mutex_unlock(&mutexCheckReadData);

        pthread_cond_signal(&matrixCreatedCondition);

        //wait for Analyzer
        pthread_cond_wait(&startedAnalyzerCondition, &mutexBuffer);

    }

    //free up Analyzer
    pthread_cond_signal(&matrixCreatedCondition);

    return 0;
}

//todo
void* runAnalyzer()
{
    //run until signal detected
    while(signalChecker == 0)
    {
        pthread_mutex_lock(&mutexCheckReadData);

        pthread_cond_wait(&matrixCreatedCondition, &mutexCheckReadData);

        //todo
        if (signalChecker == 0)
            calculateCpuUsage();

        pthread_mutex_unlock(&mutexCheckReadData);

        //free Reader
        pthread_cond_signal(&startedAnalyzerCondition);

    }
    return 0;
}
