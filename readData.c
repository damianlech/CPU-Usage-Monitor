#include "readData.h"

#include <stdio.h>

#include <stdlib.h>

void printLineFromFile()
{
    //Create a FILE pointer and append it with first line from /proc/stat file
    FILE * fPointer;

    fPointer = fopen("/proc/stat", "r");

    char singleLine[60];

    fgets(singleLine, 60, fPointer);

    fclose(fPointer);

    //print the first line of /proc/stat
    printf("%s", singleLine);
}
