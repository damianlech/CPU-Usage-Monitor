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
        PrevIdle = (float)cpuCoresAsMatrixOld[i][IDLE] + (float)cpuCoresAsMatrixOld[i][IOWAIT];
        Idle = (float)cpuCoresAsMatrix[i][IDLE] + (float)cpuCoresAsMatrix[i][IOWAIT];

        PrevNonIdle = (float)cpuCoresAsMatrixOld[i][USER] + (float)cpuCoresAsMatrixOld[i][NICE] + (float)cpuCoresAsMatrixOld[i][SYSTEM] + (float)cpuCoresAsMatrixOld[i][IRQ] + (float)cpuCoresAsMatrixOld[i][SOFTIRQ] + (float)cpuCoresAsMatrixOld[i][STEAL];
        NonIdle = (float)cpuCoresAsMatrix[i][USER] + (float)cpuCoresAsMatrix[i][NICE] + (float)cpuCoresAsMatrix[i][SYSTEM] + (float)cpuCoresAsMatrix[i][IRQ] + (float)cpuCoresAsMatrix[i][SOFTIRQ] + (float)cpuCoresAsMatrix[i][STEAL];

        PrevTotal = PrevIdle + PrevNonIdle;
        Total = Idle + NonIdle;

        totald = Total - PrevTotal;
        idled = Idle - PrevIdle;

        CPU_Percentage[i] = ((totald - idled)/totald) * 100;
    }

    return(CPU_Percentage);
}
