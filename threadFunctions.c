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
    //for (int j=0;j<10;j++)
    {
        //while(matrixCreated == 1)
            //pthread_cond_wait(&matrixCreatedCondition, &mutexBuffer);


        pthread_mutex_lock(&mutexBuffer);
        //write raw data to the matrix
        getDataFromFile();


        pthread_mutex_unlock(&mutexBuffer);
        pthread_cond_signal(&matrixCreatedCondition);
        //matrixCreated=1;
        //do it every 1 second
        if (i == 0)
            sleep(1);

        //free up memory allocated to matrix
        for (int i = 0; i < numberOfCpus; i++)
        {
            free(cpuCoresAsMatrix[i]);

        }

        free(cpuCoresAsMatrix);
        //matrixCreated = 1;
    }
    //printf("%d", i);
    pthread_cond_signal(&matrixCreatedCondition);



    return 0;
}

//todo
void* runAnalyzer()
{
    while(i == 0)
    //for (int j=0;j<10;j++)
    {
        pthread_mutex_lock(&mutexBuffer);



        pthread_cond_wait(&matrixCreatedCondition, &mutexBuffer);


        //matrixCreated=0;

        if (i == 0)
            printf("%d\n\n", cpuCoresAsMatrix[0][0]);

        pthread_mutex_unlock(&mutexBuffer);
        //matrixCreated = 0;
        //pthread_cond_wait(&matrixCreatedCondition, &mutexBuffer);
        //printf("%d", i);
    }
    //printf("%d", i);

    return 0;
}
