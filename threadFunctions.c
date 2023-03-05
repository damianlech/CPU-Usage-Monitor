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

#include "threadFunctions.h"

//mutexes and semaphores defined
pthread_mutex_t mutexCheckReadData;

pthread_mutex_t mutexWatchdog;

pthread_cond_t condReader;

pthread_cond_t condAnalyzer;

pthread_cond_t condPrinter;

sem_t semReaderEmpty;

sem_t semReaderFull;

sem_t semAnalyzerEmpty;

sem_t semAnalyzerFull;

int signalChecker = 0;

//if signal for termination is received - change to 1 which will lead to closing of all threads
void signalCheck(void)
{
    signalChecker = 1;
    printf("\nExiting program...\n");
}


//Run getDataFromFile every second and update the matrix with information
void* runReader(void)
{
    //alloc matrixes
    cpuCoresAsMatrix = malloc((unsigned long)numberOfCpus * sizeof(int *));

    for (int i = 0; i < numberOfCpus; i++)
    {
        cpuCoresAsMatrix[i] = malloc((unsigned long)numberOfStatistics * sizeof(int));
    }

    cpuCoresAsMatrixOld = malloc((unsigned long)numberOfCpus * sizeof(int *));

    for (int i = 0; i < numberOfCpus; i++)
    {
        cpuCoresAsMatrixOld[i] = malloc((unsigned long)numberOfStatistics * sizeof(int));
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

        pthread_cond_signal(&condReader);

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
void* runAnalyzer(void)
{
    //allocate memory for CPU_percentage
    CPU_Percentage = malloc((unsigned long)numberOfCpus * sizeof(int));

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

        pthread_cond_signal(&condAnalyzer);
    }
    //free up memory allocated to CPU_Percentage
    free(CPU_Percentage);

    return 0;
}

//Prints out CPU Percentage
void* runPrinter(void)
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
                    printf("Total CPU usage: %.02f%%\n", (double)CPU_Percentage[i]);
                }
                else
                {
                    printf("CPU %d usage:     %.02f%%\n", i, (double)CPU_Percentage[i]);
                }
            }
            printf("\n");
        }
        sem_post(&semAnalyzerEmpty);

        pthread_cond_signal(&condPrinter);
    }
    return 0;
}

//whenever thread finishes, it sends signal to the conditional variable. If the time between signals is longer then 2 seconds - watchdog closes the program
void* runWatchdog(void)
{

    //run until signal detected
    while(signalChecker == 0)
    {
        //read starting time
        time_t ReaderBegin = time(NULL);

        //check for signal from threads
        if(signalChecker == 0)
            pthread_cond_wait(&condReader, &mutexWatchdog);

        //read end time
        time_t ReaderEnd = time(NULL);

        //save time or close the program depending on the difference in time
        if (ReaderEnd - ReaderBegin >= 2)
        {
            printf("Time waiting for a thread Reader exceeded 2 seconds... Exiting program\n");
            signalChecker = 1;
        }
        else
        {
            if (signalChecker == 0)
                printf("The elapsed time for Reader is %ld seconds\n\n", (ReaderEnd - ReaderBegin));
        }

        //read starting time
        time_t AnalyzerBegin = time(NULL);

        //check for signal from threads
        if(signalChecker == 0)
            pthread_cond_wait(&condAnalyzer, &mutexWatchdog);

        //read end time
        time_t AnalyzerEnd = time(NULL);

        //save time or close the program depending on the difference in time
        if (AnalyzerEnd - AnalyzerBegin >= 2)
        {
            printf("Time waiting for a thread Analyzer exceeded 2 seconds... Exiting program\n");
            signalChecker = 1;
        }
        else
        {
            if (signalChecker == 0)
                printf("The elapsed time for Analyzer is %ld seconds\n\n", (AnalyzerEnd - AnalyzerBegin));
        }

        //read starting time
        time_t PrinterBegin = time(NULL);

        //check for signal from threads
        if(signalChecker == 0)
            pthread_cond_wait(&condPrinter, &mutexWatchdog);

        //read end time
        time_t PrinterEnd = time(NULL);

        //save time or close the program depending on the difference in time
        if (PrinterEnd - PrinterBegin >= 2)
        {
            printf("Time waiting for a thread Printer exceeded 2 seconds... Exiting program\n");
            signalChecker = 1;
        }
        else
        {
            if (signalChecker == 0)
                printf("The elapsed time for Printer is %ld seconds\n\n", (PrinterEnd - PrinterBegin));
        }
    }
    return 0;
}
