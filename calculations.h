#ifndef CALCULATIONS_H

#define CALCULATIONS_H

#define USER        0

#define NICE        1

#define SYSTEM      2

#define IDLE        3

#define IOWAIT      4

#define IRQ         5

#define SOFTIRQ     6

#define STEAL       7

extern float *CPU_Percentage;

float *calculateCpuUsage(void);

#endif // CALCULATIONS_H
