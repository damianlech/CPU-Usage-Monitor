#ifndef OBTAINCPUSTATISTICS_H

#define OBTAINCPUSTATISTICS_H

//Based on the data from getCpuInfo, get statistics about all cores and return them in a 2D matrix (pointer to a pointer array)

extern int **cpuCoresAsMatrix;

extern int **cpuCoresAsMatrixOld;

int **getDataFromFile();

int **getOldDataFromFile();


#endif // OBTAINCPUSTATISTICS_H
