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

float *CPU_Percentage;

float *calculateCpuUsage()
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

        CPU_Percentage[i] = ((totald - idled)/totald) * 100;

        printf("%f\n\n", CPU_Percentage[i]);
    }

    return(CPU_Percentage);
}
