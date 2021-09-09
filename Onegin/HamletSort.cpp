/**
 * @file HamletSort.cpp
 *
 * Contains declarations of text sorting functions
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "HamletSort.h"

/**
 * Scan the file with the source text and saves it in a buffer
 * @param[in] filePath path to the file
 * @param[in] nSymbols number of symbols in the file
 * @return pointer to the buffer
 */

char** readHamlet(char* filePath, int nSymbols, int nStrings)
{
    assert(filePath != nullptr);

    FILE* fileHamlet = fopen(filePath, "r");

    char* textHamlet = (char*) calloc(nSymbols + nStrings, sizeof (char));
    char** strings = (char**) calloc(nStrings, sizeof (char*));

    int maxStr = maxString(filePath);

    for (int curString = 0; curString < nStrings; ++curString) {

        strings[curString] = textHamlet;
        fgets(textHamlet, maxStr, fileHamlet);
        textHamlet += (int) strlen(strings[curString]) + 1;

        printf("%d %d %s", curString, textHamlet, strings[curString]);
    }

    fclose(fileHamlet);
    return strings;
}

/**
 * Creates a new file where puts the sorted version of the source text
 * @param[in] filePath path to the file to write in
 * @param[in] textHamlet pointer to the buffer with the sorted text
 * @param[in] nSymbols the number of symbols in the file
 */

void writeHamlet(char* filePath, char** stringsList, int nStrings)
{
    assert(stringsList != nullptr);
    assert(filePath != nullptr);

    FILE* outputHamlet = fopen(filePath, "w");

    for (int string = 0; string < nStrings; ++string)
        fputs(stringsList[string], outputHamlet);

    free(stringsList);
    fclose(outputHamlet);
}

int maxString(char* filePath)
{
    FILE* fileHamlet = fopen(filePath, "r");

    int maxString = 0;
    int curString = 0;
    char symbol = 0;

    while ((symbol = (char) fgetc(fileHamlet)) != EOF) {
        if (symbol == '\n')
            maxString = (curString > maxString) ? curString : maxString;
        else
            ++curString;
    }

    fclose(fileHamlet);
    return (curString > maxString) ? curString : maxString;
}

/**
 * Swaps two strings
 * @param[in,out] firstString pointer to the first string
 * @param[in,out] secondString pointer to the second string
 */

void swapStrings(int firstString, int secondString, char** stringsList)
{
    assert(stringsList != nullptr);

    char* temp = nullptr;

    temp = stringsList[firstString];
    stringsList[firstString] = stringsList[secondString];
    stringsList[secondString] = temp;
}

/**
 * Counts the total number of symbols
 * @param[in] filePath the path to the input file
 * @return the number of symbols
 */

int countSymbols(char* filePath)
{
    assert(filePath != nullptr);

    FILE* fileHamlet = fopen(filePath, "r");

    int nSymbols = 0;

    while (fgetc(fileHamlet) != EOF)
            ++nSymbols;

    fclose(fileHamlet);
    return nSymbols; // including the last '\0' symbol
}

/**
 * Counts the number of strings in a file
 * @param[in] filePath the path to the source file
 * @return the number of strings
 */

int countStrings(char* filePath)
{
    assert(filePath != nullptr);

    FILE* fileHamlet = fopen(filePath, "r");

    int counter = 0;
    char currentSymbol = 0;

    while ((currentSymbol = (char) fgetc(fileHamlet)) != EOF) {
        if (currentSymbol == '\n') {
            ++counter;
        }
    }

    fclose(fileHamlet);
    return counter + 1; // the last line hasn't got the '\n' symbol
}

/**
 * Sorts the file using the bubble sort applied to the strings
 * @param[in,out] textHamlet the pointer to the buffer
 * @param[in] nStrings the number of the strings
 */

void bubbleHamletSort(char** stringsList, int nStrings)
{
    assert(stringsList != nullptr);

    for (int i = 0; i < nStrings; ++i)
        for (int j = i + 1; j < nStrings; ++j)
            if (strcmp(stringsList[i], stringsList[j]) > 0)
                swapStrings(i, j, stringsList);
}
