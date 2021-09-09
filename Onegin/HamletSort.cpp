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

char* readHamlet(char* filePath, int nSymbols)
{
    assert(filePath != nullptr);

    FILE* fileHamlet = fopen(filePath, "r");

    char* textHamlet = (char*) calloc(nSymbols, sizeof (char));

    for (int curSymbol = 0; curSymbol < nSymbols; ++curSymbol)
        textHamlet[curSymbol] = (char) fgetc(fileHamlet);

    fclose(fileHamlet);
    return textHamlet;
}

/**
 * Creates a new file where puts the sorted version of the source text
 * @param[in] filePath path to the file to write in
 * @param[in] textHamlet pointer to the buffer with the sorted text
 * @param[in] nSymbols the number of symbols in the file
 */

void writeHamlet(char* filePath, char* textHamlet, int nSymbols)
{
    assert(textHamlet != nullptr);
    assert(filePath != nullptr);

    FILE* outputHamlet = fopen(filePath, "w");

    for (int symbol = 0; symbol < nSymbols; ++symbol)
        fputc(textHamlet[symbol], outputHamlet);

    free(textHamlet);
    fclose(outputHamlet);
}

/**
 * Swaps two strings
 * @param[in,out] firstString pointer to the first string
 * @param[in,out] secondString pointer to the second string
 */

void swapStrings(char* firstString, char* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);
    assert(stringLength(firstString) > 0);

    char tempStr[stringLength(firstString)] = {};

    copyString(tempStr, firstString);
    copyString(firstString, secondString);
    copyString(secondString, tempStr);
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

    return nSymbols;
}

/**
 * Copies the source string to the destination string
 * @param[in,out] destString
 * @paramp[in] sourceString
 * @return number of copied symbols
 */

void copyString(char* destString, char* sourceString)
{
    assert(sourceString != nullptr);
    assert(destString != nullptr);

    while (*sourceString != '\n') {
        *destString++ = *sourceString++;
    }

    *destString = *sourceString;
}

/**
 * Finds the pseudo string's length
 * @param[in] string
 * @return the length of the string including the '\n' symbol
 */

size_t stringLength(char* string)
{
    assert(string != nullptr);

    size_t length = 1; // we suppose that the string consists at least of one '\n' symbol

    while (*string++ != '\n')
        ++length;

    return length;
}

/**
 * Compares tow strings by its length
 * @param[in] firstString
 * @param[in] secondString
 * @return the special comparisonResult value
 */

int compareStrings(char* firstString, char* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);

    int curIndex = 0;

    while (firstString[curIndex] != '\n' && secondString[curIndex] != '\n') {
        if (firstString[curIndex] > secondString[curIndex])
            return FIRST;
        else if (secondString[curIndex] > firstString[curIndex])
            return SECOND;
        else
            ++curIndex;
    }

    int lenFirst = (int) stringLength(firstString);
    int lenSecond = (int) stringLength(secondString);

    if (lenFirst == lenSecond)
        return EQUAL;
    return (lenFirst > lenSecond) ? FIRST : SECOND;
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
 * Finds the address of the string on a certain position
 * @param[in,out] text
 * @param[in] position
 * @return pointer to the required string's beginning
 */

char* getString(char* text, int position)
{
    while (position != 0) {

        if (*text++ == '\n')
            position--;
    }

    return text;
}

void print(char* string)
{
    while (*string != '\n')
        putc(*string++, stdout);

    putc('\n', stdout);
}

/**
 * Sorts the file using the bubble sort applied to the strings
 * @param[in,out] textHamlet the pointer to the buffer
 * @param[in] nStrings the number of the strings
 */

void bubbleHamletSort(char* textHamlet, int nStrings)
{
    assert(textHamlet != nullptr);

    char* firstString = nullptr;
    char* secondString = nullptr;

    for (int i = 0; i < nStrings; ++i) {

        for (int j = i + 1; j < nStrings; ++j) {

            firstString = getString(textHamlet, i);
            secondString = getString(textHamlet, j);

            if (compareStrings(firstString, secondString) == FIRST)
                swapStrings(firstString, secondString);
        }
    }
}
