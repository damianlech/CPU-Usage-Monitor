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
        getDataFromFile();

        fflush(stdout);

        for (int i = 0; i < 3; i++)
            free(cpuCoresAsMatrix[i]);

        free(cpuCoresAsMatrix);

        sleep(1);
    }
}

