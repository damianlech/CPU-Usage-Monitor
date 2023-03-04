#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

//mutex and conditional variable defined
pthread_mutex_t mutexBuffer;

pthread_cond_t matrixCreatedCondition;

int signalChecker = 0;

//Run getDataFromFile every second and update the matrix with information
void* runReader()
{
    //run until signal detected
    while(signalChecker == 0)
    {
        pthread_mutex_lock(&mutexBuffer);

        //write raw data to the matrix
        getDataFromFile();

        pthread_mutex_unlock(&mutexBuffer);

        pthread_cond_signal(&matrixCreatedCondition);

        //do it every 1 second unless signal detected
        if (signalChecker == 0)
            sleep(1);

        //free up memory allocated to matrix
        for (int i = 0; i < numberOfCpus; i++)
        {
            free(cpuCoresAsMatrix[i]);

        }

        free(cpuCoresAsMatrix);
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
        pthread_mutex_lock(&mutexBuffer);

        pthread_cond_wait(&matrixCreatedCondition, &mutexBuffer);

        //todo
        if (signalChecker == 0)
            printf("%d\n\n", cpuCoresAsMatrix[0][0]);

        pthread_mutex_unlock(&mutexBuffer);
    }
    return 0;
}
