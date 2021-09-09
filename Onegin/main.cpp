/**
 * @file main.cpp
 *
 * @author Stas Goryainov
 * @date 04/09/2021
 * @version 2.0
 */

#include <stdio.h>
#include "HamletSort.h"

int main()
{
    char filePath[100] = {};
    printf("Enter the file path (to read): ");

    if (!scanf("%s", filePath)) {
        printf("Ooops.. Something went wrong( Try again");
    }

    int nStrings = countStrings(filePath);
    int nSymbols = countSymbols(filePath);

    char** stringsList = readHamlet(filePath, nSymbols, nStrings);
    bubbleHamletSort(stringsList, nStrings);

    printf("Enter the file path (to write in): ");

    if (!scanf("%s", filePath)) {
        printf("Ooops.. Something went wrong( Try again");
    }

    writeHamlet(filePath, stringsList, nStrings);

    return 0;
}
