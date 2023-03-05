#ifndef THREADFUNCTIONS_H

#define THREADFUNCTIONS_H

//until specified signal is sent, threads will keep running
extern int signalChecker;

//mutexes and semaphores
extern pthread_mutex_t mutexCheckReadData;

extern sem_t semEmpty;

extern sem_t semFull;

//Functions for threads to use
void* runReader(); //run reader and update global variable cpuCoresAsMatrix

void* runAnalyzer(); //read cpuCoresAsMatrix and convert it into cpu usage

void* runPrinter(); //Print out CPU usage every second

#endif // THREADFUNCTIONS_H
