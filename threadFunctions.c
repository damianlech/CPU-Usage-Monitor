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

sem_t semReaderEmpty;

sem_t semReaderFull;

sem_t semAnalyzerEmpty;

sem_t semAnalyzerFull;

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
        sem_wait(&semReaderEmpty);

        pthread_mutex_lock(&mutexCheckReadData);

        //write old data to the matrix
        getOldDataFromFile();

        if (signalChecker == 0)
            sleep(1);
        //write current data to the matrix
        getDataFromFile();

        pthread_mutex_unlock(&mutexCheckReadData);

        //post semaphore
        sem_post(&semReaderFull);
    }

    //free allocated matrixes
    for (int i = 0; i < numberOfCpus; i++)
    {
        free(cpuCoresAsMatrix[i]);
    }

    free(cpuCoresAsMatrix);

    for (int i = 0; i < numberOfCpus; i++)
    {
        free(cpuCoresAsMatrixOld[i]);
    }

    free(cpuCoresAsMatrixOld);

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
        sem_wait(&semReaderFull);

        sem_wait(&semAnalyzerEmpty);

        pthread_mutex_lock(&mutexCheckReadData);

        //Run calculate function
        if (signalChecker == 0)
            calculateCpuUsage();

        pthread_mutex_unlock(&mutexCheckReadData);

        sem_post(&semReaderEmpty);

        sem_post(&semAnalyzerFull);
    }
    //free up memory allocated to CPU_Percentage
    free(CPU_Percentage);

    return 0;
}

//Prints out CPU Percentage
void* runPrinter()
{
    //run until signal detected
    while(signalChecker == 0)
    {
        sem_wait(&semAnalyzerFull);

        if (signalChecker == 0)
        {
            for (int i = 0; i < numberOfCpus; i++)
            {
                if (i == 0)
                {
                    printf("Total CPU usage: %.02f%%\n", CPU_Percentage[i]);
                }
                else
                {
                    printf("CPU %d usage:     %.02f%%\n", i, CPU_Percentage[i]);
                }
            }
            printf("\n");
        }
        sem_post(&semAnalyzerEmpty);
    }
    return 0;
}
