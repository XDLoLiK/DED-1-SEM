/**
 * @file main.cpp
 *
 * @author Stas Goryainov
 * @date 04/09/2021
 * @version 3.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include "TextSort.h"

int main(int argc, char* argv[])
{
    printf("Text sorter\n");
    printf("By Stas Goryainov\n\n");

    char filePath[100] = {};
    printf("Enter the file path (to read): ");

    if (!scanf("%s", filePath)) {
        printf("Oops.. Something went wrong( Try again");
        return 0;
    }

    int nStrings = countSymbols(filePath, '\n') + 1; // the last string hasn't got the '\n'
    char** stringsList = readText(filePath, nStrings);

    for (int i = 1; i < nStrings; ++i) {
        printf("%d\n", compareStrings(stringsList[i], stringsList[i - 1]));
    }

    qsort((void*) stringsList, (size_t) nStrings, sizeof (char*), compareStrings);

    printf("Enter the file path (to write in): ");

    if (!scanf("%s", filePath)) {
        printf("Oops.. Something went wrong( Try again");
        return 0;
    }

    writeSorted(filePath, stringsList, nStrings);

    return 0;
}
