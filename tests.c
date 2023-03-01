#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>

#include "getCpuInfo.h"

#include "obtainCpuStatistics.h"

int main()
{
    assert(getNumberOfCpus != NULL);

    printf("Testing getCpuInfo...\n");

    assert(getnumberOfStatistics != NULL);

    printf("Success!!!\n\n");

    printf("Testing obtainCpuStatistics.c...\n");

    int **cpuCoresAsMatrix;

    int numberOfCpus = getNumberOfCpus();

    int numberOfStatistics = getnumberOfStatistics();

    cpuCoresAsMatrix = getDataFromFile(numberOfCpus, numberOfStatistics);

    assert(cpuCoresAsMatrix != NULL);

    printf("Success!!!\n\n");

}
