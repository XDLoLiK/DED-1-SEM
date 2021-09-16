/**
 * @file Help.h
 *
 * Header of help on TextSort.cpp library
 */

#ifndef ONEGIN_HELP_H
#define ONEGIN_HELP_H

#include <string.h>
#include <stdio.h>

//{------------------------------------------------------------------------------------------------
/**
 * A "family" of help functions
 */

/**
 * Prints help info into the console
 */
void getHelp();

/**
 * Finds out if the user needs help
 * @param[in] nArgs number of arguments of a command line
 * @param[in] argsList list of command line parameters
 * @return true if there's a "-help" flag, false otherwise
 */
bool userWantsHelp(int nArgs, char** argsList);
//}------------------------------------------------------------------------------------------------

#endif //ONEGIN_HELP_H
