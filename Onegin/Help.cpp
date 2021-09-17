/**
 * @file Help.cpp
 *
 * Used to get help on the work of the TextSort.cpp
 */

#include "Help.h"

bool user_WantsHelp(int nArgs, char** argsList)
{
    assert(nArgs > 0);
    assert(argsList != nullptr);

    for (int curArg = 0; curArg < nArgs; ++curArg) {
        if (strcmp(argsList[curArg], "-help") == 0)
            return true;
    }

    return false;
}

void printHelp()
{
    printf("~~Text sorter by Stas Goryainov~~\n\n"
           "~version:        4.1\n"
           "~last updated:   14/09/2021\n\n"
           "~info:           Sorts the given file in alphabetic order. In particular:\n"
           "                 Firstly, starting from the beginning of each string.\n"
           "                 Then starting from the end of each string.\n"
           "                 And then puts both variants consecutively in one file.\n"
           "                 After all, puts the source text there as well.\n\n");
}
