#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

pthread_mutex_t mutexBuffer = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t matrixCreatedCondition = PTHREAD_COND_INITIALIZER;

int matrixCreated = 0;

int i = 0;
//Run getDataFromFile every second and update the matrix with information
void* runReader()
{
    while(i == 0)
    {
        //while(matrixCreated == 1)
            //pthread_cond_wait(&matrixCreatedCondition, &mutexBuffer);

        //write raw data to the matrix
        getDataFromFile();

        //do it every 1 second
        sleep(1);

        //free up memory allocated to matrix
        for (int i = 0; i < numberOfCpus; i++)
        {
            free(cpuCoresAsMatrix[i]);
        }

        free(cpuCoresAsMatrix);

        //mutex stuff

        pthread_mutex_lock(&mutexBuffer);
        matrixCreated = 1;
        pthread_cond_signal(&matrixCreatedCondition);
        pthread_mutex_unlock(&mutexBuffer);
    }



    return 0;
}

//todo
void* runAnalyzer()
{
    while(i == 0)
    {
        pthread_mutex_lock(&mutexBuffer);
        while(matrixCreated == 0)
            pthread_cond_wait(&matrixCreatedCondition, &mutexBuffer);


        pthread_mutex_unlock(&mutexBuffer);

        printf("%d\n\n", cpuCoresAsMatrix[0][0]);

        matrixCreated = 0;
        pthread_cond_wait(&matrixCreatedCondition, &mutexBuffer);
    }

    return 0;
}
