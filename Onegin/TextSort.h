/**
 * @file HamletSort.h
 *
 * A header file for HamletSort.cpp
 * (file/text sorting library)
 */

#ifndef ONEGIN_TEXT_SORT_H
#define ONEGIN_TEXT_SORT_H

/// Max path length
const size_t MAX_PATH_SIZE = 100;

/**
 * Struct implementation of a string object
 */

typedef struct String {
    char* start = nullptr;
    size_t length = 0;
} string;

/**
 * File "class"
 */

typedef struct File {
    size_t size = 0;
    size_t strings_n = 0;
    char path[MAX_PATH_SIZE] = {};
    string* strings_list = nullptr;
    char* text = nullptr;
} file;

/**
 * Enumeration that contains all the possible
 * comparison function results
 */

enum ComparisonResult {
    EQUAL  = 0, /// if two objects are equal
    FIRST  = 1, /// if the first object is bigger
    SECOND = -1 /// if the second object is bigger
};

/**
 * Contains all the possible scan results
 */

enum ScanResult {
    SCAN_SUCCESS = 0, /// if the scan has succeeded
    SCAN_FAIL    = 1  /// if the scan has failed
};

/**
 * A "family" of swap n bytes functions
 */

void swap8(void** firstElem, void** secondElem, size_t* elemSize);
void swap16(void** firstElem, void** secondElem, size_t* elemSize);
void swap32(void** firstElem, void** secondElem, size_t* elemSize);
void swap64(void** firstElem, void** secondElem, size_t* elemSize);

/**
 * A family of getSomething functions
 */

void getHelp();
int getPath(file* fileObject);
int getInfo(file* fileObject);
char* getText(file* fileObject);
size_t getSize(file* fileObject);
string* getStrings(file* fileObject);

void freeInfo(file* fileObject);
void fputl(char* stringPtr, FILE* outputFile);
bool wantsHelp(int nArgs, char** argsList);
int countSymbols(char* filePath, char searchSymbol);
void writeSorted(const file* fileObject, const char* outputPath);
void writeUnsorted(const file* fileObject, const char* outputPath);
int compareStrings(const void* firstString, const void* secondString);
void swapElements(void* firstElem, void* secondElem, size_t elemSize);
int reverseCompareStrings(const void* firstString, const void* secondString);

#endif //ONEGIN_TEXT_SORT_H
