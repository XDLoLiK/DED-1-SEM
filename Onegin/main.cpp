/**
 * @file main.cpp
 *
 * @author Stas Goryainov
 * @date 04/09/2021
 * @version 4.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include "TextSort.h"

// TODO: fileSort()
// TODO: refactor comparator

/**
 * The main function
 * @param argc number of command line parameters
 * @param argv the list of command line parameters
 * @return exit code
 */

int main(int argc, char* argv[])
{
    if (wantsHelp(argc, argv))
        getHelp();

    file OneginFile = {};

    if (getInfo(&OneginFile) == SCAN_FAIL) {
        printf("Oops.. Something went wrong( Try again\n");
        return 0;
    }

    char outputPath[MAX_PATH_SIZE] = {};
    printf("Enter the output file path: ");

    if (!scanf("%s", outputPath)) {
        printf("Oops.. Something went wrong( Try again\n");
        return 0;
    }

    // Using the standard qsort() first
    qsort((void*) OneginFile.strings_list, OneginFile.strings_n, sizeof (string), compareStrings);
    writeSorted(&OneginFile, outputPath);
    // Then self written one
    fileSort((void*) OneginFile.strings_list, (size_t) OneginFile.strings_n, sizeof (char*), reverseCompareStrings);
    writeSorted(&OneginFile, outputPath);
    // Showing that Pushkin's genius is undebatable
    writeUnsorted(&OneginFile, outputPath);

    freeInfo(&OneginFile);

    return 0;
}
