#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>

#include <time.h>

#include "obtainCpuStatistics.h"

#include "getCpuInfo.h"

#include "calculations.h"

//mutexes and semaphores defined
pthread_mutex_t mutexCheckReadData;

pthread_mutex_t mutexWatchdog;

pthread_cond_t condWatchdog;

sem_t semReaderEmpty;

sem_t semReaderFull;

sem_t semAnalyzerEmpty;

sem_t semAnalyzerFull;

int signalChecker = 0;

//if signal for termination is received - change to 1 which will lead to closing of all threads
void signalCheck()
{
    signalChecker = 1;
    printf("\nExiting program...\n");
}

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

        pthread_cond_signal(&condWatchdog);
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

        pthread_cond_signal(&condWatchdog);
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

        pthread_cond_signal(&condWatchdog);
    }
    return 0;
}

//whenever thread finishes, it sends signal to the conditional variable. If the time between signals is longer then 2 seconds - watchdog closes the program
void* runWatchdog()
{

    //run until signal detected
    while(signalChecker == 0)
    {
        //read starting time
        time_t begin = time(NULL);

        //check for signal from threads
        if(signalChecker == 0)
            pthread_cond_wait(&condWatchdog, &mutexWatchdog);

        //read end time
        time_t end = time(NULL);

        //save time or close the program depending on the difference in time
        if (end - begin >= 2)
        {
            printf("Time waiting for a thread exceeded 2 seconds... Exiting program\n");
            signalChecker = 1;
        }
        else
        {
            if (signalChecker == 0)
                printf("The elapsed time is %ld seconds\n\n", (end - begin));
        }
    }
    return 0;
}
