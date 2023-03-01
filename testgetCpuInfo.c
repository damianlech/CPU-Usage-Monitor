#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>

#include "getCpuInfo.h"



int main()
{
    assert(getNumberOfCpus != NULL);
    assert(getnumberOfStatistics != NULL);
    printf("getCpuInfo tested succesfully. getNumberOfCpus returned %d and getNumberOfStatistics returned %d\n", getNumberOfCpus(), getnumberOfStatistics());
}
