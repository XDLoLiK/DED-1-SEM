/**
 * @file HamletSort.h
 *
 * A header file for HamletSort.cpp
 * (file/text sorting library)
 */

#ifndef HAMLET_HAMLETSORT_H
#define HAMLET_HAMLETSORT_H

char** readHamlet(char* filePath, int nSymbols, int nStrings);
int countStrings(char* filePath);
int countSymbols(char* filePath);
int maxString(char* filePath);
void swapStrings(int firstString, int secondString, char** stringsList);
void bubbleHamletSort(char** stringsList, int nStrings);
void writeHamlet(char* filePath, char** stringsList, int nStrings);

#endif //HAMLET_HAMLETSORT_H
