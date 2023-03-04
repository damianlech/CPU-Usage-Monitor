#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include "getCpuInfo.h"

#include "obtainCpuStatistics.h"

#include "calculations.h"







void calculateCpuUsage()
{


    //for (int i = 0; i < numberOfCpus; i++)



    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", cpuCoresAsMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n");

    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 10; j++)
        {

            printf("%d ", cpuCoresAsMatrixOld[i][j]);
        }
        printf("\n");
    }


    printf("\n\n\n");


}
