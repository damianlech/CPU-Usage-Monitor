#ifndef CALCULATIONS_H

#define CALCULATIONS_H

#define user        0

#define nice        1

#define system      2

#define idle        3

#define iowait      4

#define irq         5

#define softirq     6

#define steal       7

#define guest       8

#define guest_nice  9

//extern int **prevStatistics;

void calculateCpuUsage();


#endif // CALCULATIONS_H
