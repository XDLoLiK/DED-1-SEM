/**
 * @file HamletSort.cpp
 *
 * Contains declarations of text sorting functions
 */

#include "TextSort.h"

int File_ctor(File* fileObject)
{
    assert(fileObject != nullptr);

    int scanResult = user_getPath(fileObject);
    fileObject->file_ptr = fopen(fileObject->path, "r");

    assert(fileObject->file_ptr != nullptr);

    // as the last string may not contain the '\n' symbol
    fileObject->strings_n = countSymbols(fileObject->file_ptr, '\n') + 1;

    File_setSize(fileObject);
    File_readText(fileObject);

    return scanResult;
}

char* File_readText(File* fileObject)
{
    assert(fileObject != nullptr);
    assert(fileObject->file_ptr != nullptr);

    fileObject->text = (char*) calloc(fileObject->size_bytes, sizeof (char));
    assert(fileObject->text != nullptr);

    fread(fileObject->text, sizeof (char), fileObject->size_bytes, fileObject->file_ptr);
    fileObject->text[fileObject->size_bytes - 1] = '\n';

    File_setStrings(fileObject);

    rewind(fileObject->file_ptr);
    return fileObject->text;
}

String* File_setStrings(File* fileObject)
{
    assert(fileObject != nullptr);

    fileObject->strings_list = (String*) calloc(fileObject->strings_n, sizeof (String));
    assert(fileObject->strings_list != nullptr);

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

size_t File_setSize(File* fileObject)
{
    assert(fileObject != nullptr);
    assert(fileObject->file_ptr != nullptr);

    struct stat fileInfo = {};
    fstat(fileno(fileObject->file_ptr), &fileInfo);

    // we need one extra symbol for an extra '\n' (excluding all the '\r' as well)
    fileObject->size_bytes =  fileInfo.st_size + 2 - fileObject->strings_n;;

    rewind(fileObject->file_ptr);
    return fileObject->size_bytes;
}

int user_getPath(File* fileObject)
{
    assert(fileObject != nullptr);

    printf("Enter the file path (to read): ");

    // 256 is the max input file's path length
    if (!scanf("%256s", fileObject->path))
        return SCAN_FAIL;

    return SCAN_SUCCESS;
}

void writeSortedText(const File* fileObject, const char* outputPath, const char* mode)
{
    assert(fileObject != nullptr);
    assert(fileObject->strings_list != nullptr);
    assert(outputPath != nullptr);

    FILE* outputFile = nullptr;

    if (strcmp(mode, "append") == 0)
        outputFile = fopen(outputPath, "a");
    else if (strcmp(mode, "write") == 0)
        outputFile = fopen(outputPath, "w");

    assert(outputFile != nullptr);

    for (int curString = 0; curString < fileObject->strings_n; ++curString)
        fputl(fileObject->strings_list[curString].start, outputFile);

    fclose(outputFile);
}

void writeSourceText(const File* fileObject, const char* outputPath, const char* mode)
{
    assert(fileObject != nullptr);
    assert(fileObject->text != nullptr);
    assert(outputPath != nullptr);

    FILE* outputFile = nullptr;

    if (strcmp(mode, "append") == 0)
        outputFile = fopen(outputPath, "a");
    else if (strcmp(mode, "write") == 0)
        outputFile = fopen(outputPath, "w");

    assert(outputFile != nullptr);

    fwrite(fileObject->text, sizeof (char), fileObject->size_bytes, outputFile);
    fclose(outputFile);
}

int countSymbols(FILE* searchFile, char searchSymbol)
{
    assert(searchFile != nullptr);

    int nSymbols = 0;
    char curSymbol = 0;

    while ((curSymbol = (char) fgetc(searchFile)) != EOF) {
        if (curSymbol == searchSymbol)
            ++nSymbols;
    }

    rewind(searchFile);
    return nSymbols;
}

void fputl(char* string, FILE* outputFile) //!! use fputs, its faster, think of '\0'
{
    while (*string != '\n')
        fputc(*string++, outputFile);

    fputc('\n', outputFile);
}

int compareStrings(const void* firstString, const void* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);

    String* first = (String*) firstString;
    String* second = (String*) secondString;

    int curSymbol = 0;

    while (first->start[curSymbol] != '\n' && second->start[curSymbol] != '\n') {

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

int compareReversedStrings(const void* firstString, const void* secondString)
{
    assert(firstString != nullptr);
    assert(secondString != nullptr);

    String* first = (String*) firstString;
    String* second = (String*) secondString;

    size_t minLen = (first->length > second->length) ? second->length : first->length;

    for (int curSymbol = 1; curSymbol < minLen; ++curSymbol) {

        if (first->start[first->length - curSymbol] > second->start[second->length - curSymbol])
            return FIRST;
        else if (second->start[second->length - curSymbol] > first->start[first->length - curSymbol])
            return SECOND;
    }

    if (first->length == second->length)
        return EQUAL;

    return (first->length > second->length) ? FIRST : SECOND;
}

void File_dtor(File* fileObject)
{
    // frees up file's text
    free(fileObject->text);
    fileObject->text = nullptr;

    // frees up strings list
    free(fileObject->strings_list);
    fileObject->strings_list = nullptr;

    // Sets FILE* to null
    fileObject->file_ptr = nullptr;

    // Sets all the non-pointer parameters to 0
    fileObject->strings_n = 0;
    fileObject->size_bytes = 0;
    strcpy(fileObject->path, "");
}

size_t findPartition(void* start, size_t nElements, size_t elementSize, int (*comparator) (const void*, const void*))
{
    void* pivot = start;

    void* low = start;
    void* high = (char*) start + (nElements - 1) * elementSize;

    while (true) {
        while (comparator(low, pivot) == SECOND)
            low = (char*) low + elementSize;

        while (comparator(high, pivot) == FIRST)
            high = (char*) high - elementSize;

        if (low >= high)
            return ((char*) high - (char*) start) / elementSize;

        swapElements(low, high, elementSize);

        high = (char*) high - elementSize;
        low = (char*) low + elementSize;
    }
}

void quickSort(void* start, size_t nElements, size_t elementSize, int (*comparator) (const void*, const void*))
{
    assert(start != nullptr);
    assert(comparator != nullptr);

    if (nElements > 1) {
        size_t partition = findPartition(start, nElements, elementSize, comparator);
        quickSort(start, partition, elementSize, comparator);
        quickSort((char*) start + (partition + 1) * elementSize, nElements - partition - 1, elementSize, comparator);
    }
}
