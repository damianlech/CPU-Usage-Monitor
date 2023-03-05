#ifndef THREADFUNCTIONS_H

#define THREADFUNCTIONS_H

//until specified signal is sent, threads will keep running
extern int signalChecker;

//mutexes and semaphores
extern pthread_mutex_t mutexCheckReadData;

extern pthread_mutex_t mutexWatchdog;

extern pthread_mutex_t mutexQueue;

extern pthread_cond_t condReader;

extern pthread_cond_t condAnalyzer;

extern pthread_cond_t condPrinter;

extern sem_t semReaderEmpty;

extern sem_t semReaderFull;

extern sem_t semAnalyzerEmpty;

extern sem_t semAnalyzerFull;

//Functions for threads to use
void* runReader(); //run reader and update global variable cpuCoresAsMatrix

void* runAnalyzer(); //read cpuCoresAsMatrix and convert it into cpu usage

void* runPrinter(); //Print out CPU usage every second

void* runWatchdog(); //Await for signal from threads and read the time in between

void signalCheck();

#endif // THREADFUNCTIONS_H
