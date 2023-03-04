#ifndef THREADFUNCTIONS_H

#define THREADFUNCTIONS_H

//until specified signal is sent, threads will keep running
extern int signalChecker;

//mutex and conditional variable
extern pthread_mutex_t mutexBuffer;

extern pthread_mutex_t mutexBuffer2;

extern pthread_cond_t matrixCreatedCondition;

extern pthread_cond_t matrixCreatedCondition2;

//Functions for threads to use
void* runReader(); //run reader and update global variable cpuCoresAsMatrix

void* runAnalyzer(); //read cpuCoresAsMatrix and convert it into cpu usage

#endif // THREADFUNCTIONS_H
