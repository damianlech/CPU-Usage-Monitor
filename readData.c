#include "readData.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char singleLine[60];

int rawData[9];

void printLineFromFile()
{
    //Create a FILE pointer and append it with first line from /proc/stat file
    FILE * fPointer;

    fPointer = fopen("/proc/stat", "r");

    fgets(singleLine, 60, fPointer);

    fclose(fPointer);
}

void convertStringToIntegerArray()
{
    //run the function to get string from file
    printLineFromFile();

    //set up character " " to be omitted during token creation
    const char toRemove[2] = " ";

    char *token;

    //create first token, "cpu"
    token = strtok(singleLine, toRemove);

    //create tokens from the rest of the string and write them into an integer array rawData
    for (int i = 0; i < (int)(sizeof(rawData) / sizeof(rawData[0]) + 1); i++)
    {
        token = strtok(NULL, toRemove);

        rawData[i] = atoi(token);

        printf("%d ", rawData[i]);
    }
}
