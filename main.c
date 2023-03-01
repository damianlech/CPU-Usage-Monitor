/*
Program CPU Usage Monitor
Main
Author: Damian Lech
*/

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include "readData.h"

int main()
{
    int **cpuCoresAsMatrix;

    while(0 == 0)
    {
        getDataFromFile(getNumberOfCpus(), getnumberOfStatistics());

        fflush(stdout);

        sleep(1);
    }
}

