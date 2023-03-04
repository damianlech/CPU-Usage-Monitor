#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

#include "calculations.h"

//mutex and conditional variable defined
pthread_cond_t matrixCreatedCondition2;

pthread_mutex_t mutexBuffer;

pthread_mutex_t mutexBuffer2;

pthread_cond_t matrixCreatedCondition;

int signalChecker = 0;

//Run getDataFromFile every second and update the matrix with information
void* runReader()
{

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





        pthread_mutex_lock(&mutexBuffer);

        getOldDataFromFile();



        if (signalChecker == 0)
            sleep(1);
        //write raw data to the matrix
        getDataFromFile();

        pthread_mutex_unlock(&mutexBuffer);

        pthread_cond_signal(&matrixCreatedCondition);

        pthread_cond_wait(&matrixCreatedCondition2, &mutexBuffer2);








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
            calculateCpuUsage();




        pthread_mutex_unlock(&mutexBuffer);


        pthread_cond_signal(&matrixCreatedCondition2);

    }
    return 0;
}
