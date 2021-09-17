/**
 * @file main.cpp
 *
 * @author Stas Goryainov
 * @date 04/09/2021
 * @version 4.1
 */

#include "Help.h"
#include "TextSort.h"

int main(int argc, char* argv[])
{
    if (user_WantsHelp(argc, argv))
        printHelp();

    File OneginFile = {};

    if (File_ctor(&OneginFile) == SCAN_FAIL) {
        printf("ERROR: main(): unable to construct the File object\n");
        return 0;
    }

    char outputPath[MAX_PATH_SIZE] = {};
    printf("Enter the output file path: ");

    // 256 is the max output file's path length
    if (!scanf("%256s", outputPath)) {
        printf("ERROR: main(): output path scan fail\n");
        return 0;
    }

    // Using the standard qsort() first
    qsort((void*) OneginFile.strings_list, OneginFile.strings_n, sizeof (String), compareStrings);
    writeSortedText(&OneginFile, outputPath, "append");

    // Then self written one
    quickTextSort((void*) OneginFile.strings_list, (size_t) OneginFile.strings_n, sizeof (String), reverseCompareStrings);
    writeSortedText(&OneginFile, outputPath, "append");

    // Showing that Pushkin's genius is undebatable
    writeSourceText(&OneginFile, outputPath, "append");

    File_dtor(&OneginFile);
    return 0;
}
