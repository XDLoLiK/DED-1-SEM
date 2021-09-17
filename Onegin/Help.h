/**
 * @file Help.h
 *
 * Header of help on TextSort.cpp library
 */

#ifndef ONEGIN_HELP_H
#define ONEGIN_HELP_H

#include <string.h>
#include <stdio.h>
#include <assert.h>

//{------------------------------------------------------------------------------------------------
/**
 * A "family" of help functions
 */

/**
 * Prints help info into the console
 */
void printHelp();

/**
 * Finds out if the user needs help
 * @param[in] nArgs number of arguments of a command line
 * @param[in] argsList list of command line parameters
 * @return true if there's a "-help" flag, false otherwise
 */
bool user_WantsHelp(int nArgs, char** argsList);
//}------------------------------------------------------------------------------------------------

#endif //ONEGIN_HELP_H
