/**
* @file Terminal.h
*/


#ifndef PROCESSOR_CONFIG_H
#define PROCESSOR_CONFIG_H


#include <string.h>

#include "..\..\general\Errors.h"

#include "..\Processor\Processor.h"
#include "..\Assembler\Assembler.h"
#include "..\Disassembler\Disassembler.h"


//{--------------------------------------------------------Constants-----------------------------------------------------------------------

const int MAX_CD_PATH_SIZE 		   = 256;
const int MAX_DIRECTORY_SIZE 	   = 32;
const int MAX_PROCESS_NAME_LENGTH  = 12;
const int MAX_EXECUTABLE_PATH_SIZE = 64; 

//}----------------------------------------------------------------------------------------------------------------------------------------


/**
 * @brief      Called on help.
 */
void ON_HELP();


/**
 * @brief      Called on compile.
 *
 * @return     The error's code
 */
ERROR_CODES ON_COMPILE();


/**
 * @brief      Called on execute.
 *
 * @return     The error's code
 */
ERROR_CODES ON_EXECUTE();


/**
 * @brief      Called on decompile.
 *
 * @return     The error's code
 */
ERROR_CODES ON_DECOMPILE();	


/**
 * @brief      Goes one directory back
 *
 * @param      path  The current path
 *
 * @return     The error's code
 */
ERROR_CODES GO_BACK(char* path);	   	


/**
 * @brief      Called on change directory
 *
 * @param      path  The current path
 *
 * @return     The error's code
 */
ERROR_CODES ON_CHANGE_DIRECTORY(char* path);


/**
 * @brief      Goes one directory forward
 *
 * @param      path       The current path
 * @param      directory  The directory to go to
 *
 * @return     The error's code
 */
ERROR_CODES GO_FORWARD(char* path, char* directory);


#endif // PROCESSOR_CONFIG_H
