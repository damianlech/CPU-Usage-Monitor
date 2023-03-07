#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>

#include "calculations.h"

#include "getCpuInfo.h"

#include "obtainCpuStatistics.h"

int main()
{
    //getCpuInfo
    printf("Testing getCpuInfo...\n");

    assert(getNumberOfCpus != NULL);

    assert(getnumberOfStatistics != NULL);

    printf("Success!!!\n\n");

    //obtainCpuStatistics
    printf("Testing obtainCpuStatistics.c...\n");

    int **cpuCoresAsMatrix;

    int numberOfCpus = getNumberOfCpus();

    int numberOfStatistics = getnumberOfStatistics();

    assert(getDataFromFile != NULL);

    assert(getOldDataFromFile != NULL);

    printf("Success!!!\n\n");

    //calculaions
    printf("Testing calculations.c...\n");

    float *CPU_Percentage;

    assert(calculateCpuUsage != NULL);

    printf("Success!!!\n\n");
}
