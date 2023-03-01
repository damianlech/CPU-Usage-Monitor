#ifndef READATA_H

#define READATA_H

/*
This function will:
1. read the file
2. get the number of lines starting with "cpu" to get the number of cores in the system
3. using strtok from string.h create tokens based on strings pulled from the file
4. put the tokens as variables into a dynamic integer matrix
*/

void getDataFromFile();

#endif // READATA_H
