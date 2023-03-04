#ifndef THREADFUNCTIONS_H

#define THREADFUNCTIONS_H

//until specified signal is sent, threads will keep running
extern int signalChecker;

//mutexes and conditional variable
extern pthread_mutex_t mutexCheckReadData;

extern pthread_mutex_t mutexBuffer;

extern pthread_cond_t matrixCreatedCondition;

extern pthread_cond_t startedAnalyzerCondition;

//Functions for threads to use
void* runReader(); //run reader and update global variable cpuCoresAsMatrix

void* runAnalyzer(); //read cpuCoresAsMatrix and convert it into cpu usage

#endif // THREADFUNCTIONS_H
