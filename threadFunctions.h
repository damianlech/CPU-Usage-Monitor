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
void *runReader(void); //run reader and update global variable cpuCoresAsMatrix

void *runAnalyzer(void); //read cpuCoresAsMatrix and convert it into cpu usage

void *runPrinter(void); //Print out CPU usage every second

void *runWatchdog(void); //Await for signal from threads and read the time in between

void signalCheck(void);



#endif // THREADFUNCTIONS_H
