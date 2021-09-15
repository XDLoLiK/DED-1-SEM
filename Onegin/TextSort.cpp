/**
 * @file HamletSort.cpp
 *
 * Contains declarations of text sorting functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>
#include <inttypes.h>
#include "TextSort.h"

/**
 * Gets all the file info
 * @param fileObject pointer to the file "object"
 * @return special ScanResult value
 */

int getInfo(file* fileObject)
{
    assert(fileObject != nullptr);

    int result = getPath(fileObject);

    // as the last string may not contain the '\n' symbol
    fileObject->strings_n = countSymbols(fileObject->path, '\n') + 1;

    getSize(fileObject);
    getText(fileObject);

    return result;
}

/**
 * Scan the file text
 * @param fileObject pointer to the file "object"
 * @return pointer to the text start
 */

char* getText(file* fileObject)
{
    assert(fileObject != nullptr);

    FILE* inputFile = fopen(fileObject->path, "r");

    char* textPtr = (char*) calloc(fileObject->size, sizeof (char));
    fileObject->text = textPtr;

    fread(fileObject->text, sizeof (char), fileObject->size, inputFile);

    fileObject->text[fileObject->size] = '\n';
    getStrings(fileObject);

    fclose(inputFile);
    return textPtr;
}

/**
 * Creates and fulfills a strings list for a file "object"
 * @param fileObject pointer to the file "object"
 * @return pointer to the strings list start
 */

string* getStrings(file* fileObject)
{
    assert(fileObject != nullptr);

    fileObject->strings_list = (string*) calloc(fileObject->strings_n, sizeof (string));
    fileObject->strings_list[0].start = fileObject->text;

    char* buffer = fileObject->text;
    int curString = 1;
    int curLength = 1;

    while (curString < fileObject->strings_n) { 
        if (*buffer == '\n') {
            fileObject->strings_list[curString].start = buffer + 1;
            fileObject->strings_list[curString - 1].length = curLength;

            curLength = 0;
            ++curString;
        }

        ++curLength;
        ++buffer;
    }

    fileObject->strings_list[curString - 1].length = curLength;

    return fileObject->strings_list;
}

/**
 * Scans the size of a file "object"
 * @param fileObject pointer to the file "object"
 * @return size of file in bytes excluding the '\r' symbols (or simply the number of chars)
 */

size_t getSize(file* fileObject)
{
    assert(fileObject != nullptr);

    FILE* inputFile = fopen(fileObject->path, "r");

    struct stat fileInfo = {};
    fstat(fileno(inputFile), &fileInfo);

    // we need one extra symbol for an extra '\n'
    size_t fileSize  = fileInfo.st_size + 1 - fileObject->strings_n;
    fileObject->size = fileSize;

    fclose(inputFile);
    return fileSize;
}

/**
 * Gets the "to read" file path from the user
 * @param[in,out] fileObject the pointer to the file "object"
 * @return special ScanResult value
 */

int getPath(file* fileObject)
{
    printf("Enter the file path (to read): ");

    if (!scanf("%s", fileObject->path))
        return SCAN_FAIL;

    return SCAN_SUCCESS;
}

/**
 * Puts the sorted version of the source text to the output file
 * @param[in] fileObject pointer to the file "object"
 * @param[in] outputPath the output file path
 */

void writeSorted(const file* fileObject, const char* outputPath)
{
    assert(fileObject->strings_list != nullptr);
    assert(outputPath != nullptr);

    FILE* outputFile = fopen(outputPath, "a");

    for (int curString = 0; curString < fileObject->strings_n; ++curString)
        fputl(fileObject->strings_list[curString].start, outputFile);

    fputc('\n', outputFile);
    fclose(outputFile);
}

/**
 * Puts the unsorted version of the source text to the output file
 * @param fileObject the copy of the file "object"
 * @param outputPath
 */

void writeUnsorted(const file* fileObject, const char* outputPath)
{
    assert(fileObject->text != nullptr);
    assert(outputPath != nullptr);

    FILE* outputFile = fopen(outputPath, "a");

    fwrite(fileObject->text, sizeof (char), fileObject->size, outputFile);
    fputc('\n', outputFile);

    fclose(outputFile);
}

/**
 * Swaps two strings' pointers in the list
 * @param[in,out] firstString pointer to the first element
 * @param[in,out] secondString pointer to the second element
 * @param[in] elemSize size of 1 element
 */

void swapElements(void* firstElem, void* secondElem, size_t elemSize)
{
    assert(firstElem != nullptr);
    assert(secondElem != nullptr);

    while (elemSize > 0) {
        swap64(&firstElem, &secondElem, &elemSize);
        swap32(&firstElem, &secondElem, &elemSize);
        swap16(&firstElem, &secondElem, &elemSize);
        swap8(&firstElem, &secondElem, &elemSize);
    }
}

/**
 * Swaps 8 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */

void swap8(void** firstElem, void** secondElem, size_t* elemSize)
{
    while (*elemSize >= 1) {
        uint8_t buffer = *((uint8_t*) (*firstElem));
        *((uint8_t*) (*firstElem)) = *((uint8_t*) (*secondElem));
        *((uint8_t*) (*secondElem)) = buffer;

        *elemSize -= 1;

        *firstElem = (uint8_t*) (*firstElem) + 1;
        *secondElem = (uint8_t*) (*secondElem) + 1;
    }
}

/**
 * Swaps 16 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */

void swap16(void** firstElem, void** secondElem, size_t* elemSize)
{
    while (*elemSize >= 2) {
        uint16_t buffer = *((uint16_t*) (*firstElem));
        *((uint16_t*) (*firstElem)) = *((uint16_t*) (*secondElem));
        *((uint16_t*) (*secondElem)) = buffer;

        *elemSize -= 2;

        *firstElem = (uint16_t*) (*firstElem) + 1;
        *secondElem = (uint16_t*) (*secondElem) + 1;
    }
}

/**
 * Swaps 32 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */

void swap32(void** firstElem, void** secondElem, size_t* elemSize)
{
    while (*elemSize >= 4) {
        uint32_t buffer = *((uint32_t*) (*firstElem));
        *((uint32_t*) (*firstElem)) = *((uint32_t*) (*secondElem));
        *((uint32_t*) (*secondElem)) = buffer;

        *elemSize -= 4;

        *firstElem = (uint32_t*) (*firstElem) + 1;
        *secondElem = (uint32_t*) (*secondElem) + 1;
    }
}

/**
 * Swaps 64 bits of two elements while possible
 * @param[in,out] firstElem pointer to the pointer to the first element
 * @param[in,out] secondElem pointer to the pointer to the second element
 * @param[in,out] elemSize pointer to the size left to swap
 */

void swap64(void** firstElem, void** secondElem, size_t* elemSize)
{
    while (*elemSize >= 8) {
        uint64_t buffer = *((uint64_t*) (*firstElem));
        *((uint64_t*) (*firstElem)) = *((uint64_t*) (*secondElem));
        *((uint64_t*) (*secondElem)) = buffer;

        *elemSize -= 8;

        *firstElem = (uint64_t*) (*firstElem) + 1;
        *secondElem = (uint64_t*) (*secondElem) + 1;
    }
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
 * Finds out if the user needs help
 * @param[in] nArgs number of arguments of a command line
 * @param[in] argsList list of command line parameters
 * @return true if there's a "-help" flag, false otherwise
 */

bool wantsHelp(int nArgs, char** argsList)
{
    for (int curArg = 0; curArg < nArgs; ++curArg)
        if (strcmp(argsList[curArg], "-help") == 0)
            return true;

    return false;
}

/**
 * Prints help info to the console
 */

void getHelp()
{
    printf("~~Text sorter by Stas Goryainov~~\n\n"
           "~version:        4.1\n"
           "~last updated:   14/09/2021\n\n"
           "~info:           Sorts the given file in alphabetic order. In particular:\n"
           "                 Firstly, starting from the beginning of each string.\n"
           "                 Then starting from the end of each string.\n"
           "                 And then puts both variants consecutively in one file.\n"
           "                 After all, puts the source text there as well.\n");
}

/**
 * Compares two strings (starting from the beginning)
 * @param[in] firstString pointer to the first string
 * @param[in] secondString pointer to the second string
 * @return a special ComparisonResult value
 */

int compareStrings(const void* firstString, const void* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);

    string* first = (string*) firstString;
    string* second = (string*) secondString;

    int curSymbol = 0;

    while (first->start[curSymbol] != '\n' || second->start[curSymbol] != '\n') {

        if (first->start[curSymbol] > second->start[curSymbol])
            return FIRST;
        else if (second->start[curSymbol] > first->start[curSymbol])
            return SECOND;

        ++curSymbol;
    }

    if (first->length == second->length)
        return EQUAL;

    return (first->length > second->length) ? FIRST : SECOND;
}

/**
 * Compares two strings (starting from the end)
 * @param[in] firstString pointer to the first string
 * @param[in] secondString pointer to the second string
 * @return a special ComparisonResult value
 */

int reverseCompareStrings(const void* firstString, const void* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);

    string* first = (string*) firstString;
    string* second = (string*) secondString;

    int minLen = (first->length > second->length) ? second->length : first->length;

    for (int curSymbol = 0; curSymbol < minLen; ++curSymbol) {

        if (first->start[first->length - curSymbol] > second->start[second->length - curSymbol]) {
            return FIRST;
        } else if (second->start[second->length - curSymbol] > first->start[first->length - curSymbol]) {
            return SECOND;
        }
    }

    if (first->length == second->length)
        return EQUAL;

    return (first->length > second->length) ? FIRST : SECOND;
}

/**
 * Frees up the memory used by file "object"
 * @param[in,out] fileObject pointer to the file "object"
 */

void freeInfo(file* fileObject)
{
    // frees up file's text
    free(fileObject->text);
    fileObject->text = nullptr;

    // frees up strings list
    free(fileObject->strings_list);
    fileObject->strings_list = nullptr;
}

/**
 *
 * @return
 */

int getPartition()
{
    return 0;
}

/**
 * Sorts the file using the bubble sort applied to the strings
 * @param[in,out] buffer the pointer to the buffer
 * @param[in] nStrings the number of the strings
 */

void quickTextSort(void* start, size_t nElements, size_t elementSize, int (*comparator) (const void*, const void*))
{
    assert(start != nullptr);
    assert(comparator != nullptr);

    if (nElements > 1) {
        size_t partition = getPartition();
        quickTextSort(start, partition, elementSize, comparator);
        quickTextSort((void*) ((char*) start + (partition + 1)), nElements - partition, elementSize, comparator);
    }
}
