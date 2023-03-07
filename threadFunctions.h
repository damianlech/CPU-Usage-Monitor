#ifndef THREADFUNCTIONS_H

#define THREADFUNCTIONS_H

//until specified signal is sent, threads will keep running
extern int signalChecker;

//mutexes and semaphores
extern pthread_mutex_t mutexCheckReadData;

extern pthread_mutex_t mutexWatchdog;

extern pthread_cond_t condWatchdog;

extern pthread_mutex_t mutexLogger;

extern pthread_cond_t condLogger;

extern sem_t semReaderEmpty;

extern sem_t semReaderFull;

extern sem_t semAnalyzerEmpty;

extern sem_t semAnalyzerFull;

//Functions for threads to use
void* runReader(void *); //run reader and update global variable cpuCoresAsMatrix

void* runAnalyzer(void *); //read cpuCoresAsMatrix and convert it into cpu usage

void* runPrinter(void *); //Print out CPU usage every second

void* runWatchdog(void *); //Await for signal from threads and read the time in between

void* runLogger(void *); //Write debug info to file

void signalCheck(int); //check for terminate signal



#endif // THREADFUNCTIONS_H
