#ifndef THREADFUNCTIONS_H

#define THREADFUNCTIONS_H

//Functions for threads to use

extern int i;

//extern int matrixCreated;

extern pthread_mutex_t mutexBuffer;

void* runReader(); //run reader and update global variable cpuCoresAsMatrix

void* runAnalyzer(); //read cpuCoresAsMatrix and convert it into cpu usage

#endif // THREADFUNCTIONS_H
