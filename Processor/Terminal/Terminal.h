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
void OnHelp();


/**
 * @brief      Called on compile.
 *
 * @return     The error's code
 */
ERROR_CODES OnCompile();


/**
 * @brief      Called on execute.
 *
 * @return     The error's code
 */
ERROR_CODES OnExecute();


/**
 * @brief      Called on decompile.
 *
 * @return     The error's code
 */
ERROR_CODES OnDecompile();	


/**
 * @brief      Goes one directory back
 *
 * @param      path  The current path
 *
 * @return     The error's code
 */
ERROR_CODES GoBack(char* path);	   	


/**
 * @brief      Called on change directory
 *
 * @param      path  The current path
 *
 * @return     The error's code
 */
ERROR_CODES OnChangeDirectory(char* path);


/**
 * @brief      Goes one directory forward
 *
 * @param      path       The current path
 * @param      directory  The directory to go to
 *
 * @return     The error's code
 */
ERROR_CODES GoForward(char* path, char* directory);


#endif // PROCESSOR_CONFIG_H
