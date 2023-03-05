#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include "getCpuInfo.h"

#include "obtainCpuStatistics.h"

#include "calculations.h"

/*
    PrevIdle = previdle + previowait
    Idle = idle + iowait

    PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
    NonIdle = user + nice + system + irq + softirq + steal

    PrevTotal = PrevIdle + PrevNonIdle
    Total = Idle + NonIdle

    # differentiate: actual value minus the previous one
    totald = Total - PrevTotal
    idled = Idle - PrevIdle

    CPU_Percentage = (totald - idled)/totald
*/

int *CPU_Percentage;

void calculateCpuUsage()
{
    float PrevIdle, Idle, PrevNonIdle, NonIdle, PrevTotal, Total, totald, idled;



    for (int i = 0; i < numberOfCpus; i++)
    {
        PrevIdle = cpuCoresAsMatrixOld[i][IDLE] + cpuCoresAsMatrixOld[i][IOWAIT];
        Idle = cpuCoresAsMatrix[i][IDLE] + cpuCoresAsMatrix[i][IOWAIT];

        PrevNonIdle = cpuCoresAsMatrixOld[i][USER] + cpuCoresAsMatrixOld[i][NICE] + cpuCoresAsMatrixOld[i][SYSTEM] + cpuCoresAsMatrixOld[i][IRQ] + cpuCoresAsMatrixOld[i][SOFTIRQ] + cpuCoresAsMatrixOld[i][STEAL];
        NonIdle = cpuCoresAsMatrix[i][USER] + cpuCoresAsMatrix[i][NICE] + cpuCoresAsMatrix[i][SYSTEM] + cpuCoresAsMatrix[i][IRQ] + cpuCoresAsMatrix[i][SOFTIRQ] + cpuCoresAsMatrix[i][STEAL];

        PrevTotal = PrevIdle + PrevNonIdle;
        Total = Idle + NonIdle;

        totald = Total - PrevTotal;
        idled = Idle - PrevIdle;

        float hmm = ((totald - idled)/totald) * 100;

        printf("%f, %f, %f\n\n",totald, idled, hmm);

        fflush(stdout);
    }

    for (int i = 0; i< numberOfCpus; i++)
    {
        for (int j = 0; j<numberOfStatistics; j++)
            printf("%d ", cpuCoresAsMatrixOld[i][j]);
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i< numberOfCpus; i++)
    {
        for (int j = 0; j<numberOfStatistics; j++)
            printf("%d ", cpuCoresAsMatrix[i][j]);
        printf("\n");
    }
}
