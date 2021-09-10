/**
 * @file HamletSort.h
 *
 * A header file for HamletSort.cpp
 * (file/text sorting library)
 */

#ifndef ONEGIN_TEXT_SORT_H
#define ONEGIN_TEXT_SORT_H

enum ComparisonResult {
    EQUAL = 0,
    FIRST = 1,
    SECOND = -1
};

int stringLength(char* string);
void fputl(char* string, FILE* outputFile);
char** readText(char* filePath, int nStrings);
int countSymbols(char* filePath, char searchSymbol);
void writeSorted(char* filePath, char** stringsList, int nStrings);
int compareStrings(const void* firstString, const void* secondString);
void swapStrings(int firstString, int secondString, char** stringsList);
int reverseCompareStrings(const void* firstString, const void* secondString);

#endif //ONEGIN_TEXT_SORT_H
