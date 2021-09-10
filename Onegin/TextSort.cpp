/**
 * @file HamletSort.cpp
 *
 * Contains declarations of text sorting functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>
#include "TextSort.h"

/**
 * Scans the file with the source text and saves it in a buffer
 * @param[in] filePath path to the input file
 * @param[in] nStrings number of strings in the file
 * @return pointer to the buffer
 */

char** readText(char* filePath, int nStrings)
{
    assert(filePath != nullptr);

    FILE* inputFile = fopen(filePath, "r");

    struct stat fileInfo = {};
    fstat(fileno(inputFile), &fileInfo);

    // we need 1 extra symbol for the last string's '\n'
    char* buffer = (char*) calloc(fileInfo.st_size + 1, sizeof (char));
    char** stringsList = (char**) calloc(nStrings, sizeof (char*));

    fread(buffer, sizeof (char), fileInfo.st_size + 1, inputFile);
    buffer[fileInfo.st_size] = '\n';

    stringsList[0] = buffer;
    int count = 1;

    while (count < nStrings) {
        if (*buffer == '\n')
            stringsList[count++] = buffer + 1;

        ++buffer;
    }

    fclose(inputFile);
    return stringsList;
}

/**
 * Creates a new file where puts the sorted version of the source text
 * @param[in] filePath path to the file to write in
 * @param[in] buffer pointer to the buffer with the sorted text
 * @param[in] nStrings the number of strings in the file
 */

void writeSorted(char* filePath, char** stringsList, int nStrings)
{
    assert(stringsList != nullptr);
    assert(filePath != nullptr);

    FILE* outputFile = fopen(filePath, "w");

    for (int string = 0; string < nStrings; ++string)
        fputl(stringsList[string], outputFile);

    free(stringsList);
    fclose(outputFile);
}

/**
 * Swaps two strings' pointers in the list
 * @param[in] firstString pointer to the first string
 * @param[in] secondString pointer to the second string
 * @param[in,out] stringsList pointer to the list of strings
 */

void swapStrings(int firstString, int secondString, char** stringsList)
{
    assert(stringsList != nullptr);

    char* temporary = nullptr;

    temporary = stringsList[firstString];
    stringsList[firstString] = stringsList[secondString];
    stringsList[secondString] = temporary;
}

/**
 * Counts the total number of given symbols
 * @param[in] filePath the path to the input file
 * @param[in] searchSymbol the symbol to search for
 * @return the number of symbols
 */

int countSymbols(char* filePath, char searchSymbol)
{
    assert(filePath != nullptr);

    FILE* inputFile = fopen(filePath, "r");

    int nSymbols = 0;
    char curSymbol = 0;

    while ((curSymbol = (char) fgetc(inputFile)) != EOF)
        if (curSymbol == searchSymbol)
            ++nSymbols;

    fclose(inputFile);
    return nSymbols;
}

/**
 * Works just like fputs, but with '\n' instead of '\0' at he end
 * @param[in, out] string pointer to the string to print
 * @param[in] outputFile file object to put the string in
 */

void fputl(char* string, FILE* outputFile)
{
    while (*string != '\n')
        fputc(*string++, outputFile);

    fputc('\n', outputFile);
}

/**
 * Computes the length of the string ending with a '\n'
 * @param[in] string pointer to the string to count symbols in
 * @return the length of a given string
 */

int stringLength(char* string)
{
    int length = 0;

    while (*string++ != '\n')
        ++length;

    return length + 1;
}

/**
 * Compares two strings (from their beginnings)
 * @param[in] firstString pointer to the first string
 * @param[in] secondString pointer to the second string
 * @return a special ComparisonResult value
 */

int compareStrings(const void* firstString, const void* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);

    char* first = (char*) firstString;
    char* second = (char*) secondString;

    int lenFirst = stringLength(first);
    int lenSecond = stringLength(second);
    int minLen = (lenFirst < lenSecond) ? lenSecond : lenFirst;

    for (int curSymbol = 0; curSymbol < minLen; ++curSymbol) {

        if (first[curSymbol] > second[curSymbol]) {
            return FIRST;
        } else if (second[curSymbol] > first[curSymbol]) {
            return SECOND;
        }
    }

    if (lenFirst == lenSecond)
        return EQUAL;

    return (lenFirst > lenSecond) ? FIRST : SECOND;
}

/**
 * Compares two strings (from their ends)
 * @param[in] firstString pointer to the first string
 * @param[in] secondString pointer to the second string
 * @return a special ComparisonResult value
 */

int reverseCompareStrings(const void* firstString, const void* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);

    char* first = (char*) firstString;
    char* second = (char*) secondString;

    int lenFirst = stringLength(first);
    int lenSecond = stringLength(second);
    int minLen = (lenFirst < lenSecond) ? lenSecond : lenFirst;

    for (int curSymbol = 0; curSymbol < minLen; ++curSymbol) {

        if (first[lenFirst - curSymbol] > second[lenSecond - curSymbol]) {
            return FIRST;
        } else if (second[curSymbol] > first[curSymbol]) {
            return SECOND;
        }
    }

    if (lenFirst == lenSecond)
        return EQUAL;

    return (lenFirst > lenSecond) ? FIRST : SECOND;
}

int getPartion()
{
    return 0;
}

/**
 * Sorts the file using the bubble sort applied to the strings
 * @param[in,out] buffer the pointer to the buffer
 * @param[in] nStrings the number of the strings
 */

void quickTextSort(char** stringsList, int nStrings)
{
    assert(stringsList != nullptr);


}
