/**
 * @file HamletSort.h
 *
 * A header file for HamletSort.cpp
 * (file/text sorting library)
 */

#ifndef ONEGIN_TEXT_SORT_H
#define ONEGIN_TEXT_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>
#include <inttypes.h>

#include "Swapper.h"

/// Max path length
const size_t MAX_PATH_SIZE = 256;

//{------------------------------------------------------------------------------------------------
/**
 * Struct implementation of a string object
 */
typedef struct string {
    size_t length = 0;
    char* start = nullptr;
} String;
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * File "class"
 */
typedef struct file {
    size_t strings_n = 0;
    size_t size_bytes = 0;
    char path[MAX_PATH_SIZE] = {};
    char* text = nullptr;
    FILE* file_ptr = nullptr;
    String* strings_list = nullptr;
} File;
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Enumeration that contains all the possible
 * comparison function results
 */
enum ComparisonResult {
    EQUAL  =  0, /// if two objects are equal
    FIRST  =  1, /// if the first object is bigger
    SECOND = -1  /// if the second object is bigger
};
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Contains all the possible scan results
 */
enum ScanResult {
    SCAN_SUCCESS = 0, /// if the scan has succeeded
    SCAN_FAIL    = 1  /// if the scan has failed
};
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Working with File "class" functions
 */
/**

 * Gets the "to read" file path from the user
 * @param[in,out] fileObject the pointer to the file "object"
 * @return special ScanResult value
 */
int user_getPath(File* fileObject);

/**
 * Counts the total number of given symbols
 * @param[in] searchFile the pointer to the input file
 * @param[in] searchSymbol the symbol to search for
 * @return the number of symbols
 */
int countSymbols(FILE* searchFile, char searchSymbol);

/**
 * Initialises a File "object"
 * @param fileObject pointer to the file "object"
 * @return special ScanResult value
 */
int File_ctor(File* fileObject);

/**
 * Scan the text from the file
 * @param fileObject pointer to the file "object"
 * @return pointer to the text start
 */
char* File_readText(File* fileObject);

/**
 * Sets the size of a file "object"
 * @param fileObject pointer to the file "object"
 * @return size of file in bytes excluding the '\r' symbols (or simply the number of chars)
 */
size_t File_setSize(File* fileObject);

/**
 * Creates and fulfills a strings list for a file "object"
 * @param fileObject pointer to the file "object"
 * @return pointer to the strings list start
 */
String* File_setStrings(File* fileObject);

/**
 * Frees up the memory used by file "object"
 * @param[in,out] fileObject pointer to the file "object"
 */
void File_dtor(File* fileObject);
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Functions related to writing something
 */

/**
 * Works just like fputs, but with '\n' instead of '\0' at he end
 * @param[in, out] string pointer to the string to print
 * @param[in] outputFile file object to put the string in
 */
void fputl(char* stringPtr, FILE* outputFile);

/**
 * Puts the sorted version of the source text to the output file
 * @param[in] fileObject pointer to the file "object"
 * @param[in] outputPath the output file path
 */
void writeSortedText(const File* fileObject, const char* outputPath, const char* mode);

/**
 * Puts the unsorted version of the source text to the output file
 * @param fileObject the copy of the file "object"
 * @param outputPath
 */
void writeSourceText(const File* fileObject, const char* outputPath, const char* mode);
//}------------------------------------------------------------------------------------------------

//{------------------------------------------------------------------------------------------------
/**
 * Functions related to sorting
 */

/**
 * Compares two strings (starting from the beginning)
 * @param[in] firstString pointer to the first string
 * @param[in] secondString pointer to the second string
 * @return a special ComparisonResult value
 */
int compareStrings(const void* firstString, const void* secondString);

/**
 * Compares two strings (starting from the end)
 * @param[in] firstString pointer to the first string
 * @param[in] secondString pointer to the second string
 * @return a special ComparisonResult value
 */
int compareReversedStrings(const void* firstString, const void* secondString);

/**
 * Sorts a given data set using the quick sort and a given comparator function
 * @param[in,out] start the beginning of a data set to sort
 * @param[in] nElements the number of elements in a data set
 * @param[in] elementSize the of a single element
 * @param[in] comparator pointer to the comparator function
 */
void quickSort(void* start, size_t nElements, size_t elementSize, int (*comparator) (const void*, const void*));

/**
 * Finds the partition in which an element divides the data set
 * @param[in] start start of the data set
 * @param[in] nElements number of elements to check
 * @param[in] elementSize size of a single element
 * @param[in] comparator pointer to the comparator function
 * @return the partition
 */
size_t findPartition(void* start, size_t nElements, size_t elementSize, int (*comparator) (const void*, const void*));
//}------------------------------------------------------------------------------------------------

#endif //ONEGIN_TEXT_SORT_H
