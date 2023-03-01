#ifndef READATA_H

#define READATA_H

/*
The purpose of these two functions is to:
1. open and read /proc/stat using printLineFromFile to get a first line as a string
2. convert that string to a usable integer array using convertStringToIntegerArray
*/

void printLineFromFile();

void convertStringToIntegerArray();

#endif // READATA_H
