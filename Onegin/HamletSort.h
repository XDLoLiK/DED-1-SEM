/**
 * @file HamletSort.h
 *
 * A header file for HamletSort.cpp
 * (file/text sorting library)
 */

#ifndef HAMLET_HAMLETSORT_H
#define HAMLET_HAMLETSORT_H

/**
 * Enlists all possible string comparison outcomes
 */

enum comparisonResult {
    FIRST  = 1, /// If the first one is bigger
    EQUAL  = 0, /// If strings are equal
    SECOND = 1  /// If the second one is bigger
};

void print(char* string);
char* readHamlet(char* filePath, int nSymbols);
int countStrings(char* filePath);
int countSymbols(char* filePath);
void swapStrings(char* firstString, char* secondString);
size_t stringLength(char* string);
int compareStrings(char* firstString, char* secondString);
void copyString(char* destString, char* sourceString);
void bubbleHamletSort(char* textHamlet, int nStrings);
char* getString(char* text, int position);
void writeHamlet(char* filePath, char* textHamlet, int nSymbols);

#endif //HAMLET_HAMLETSORT_H
