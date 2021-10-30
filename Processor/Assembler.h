/**
 * @file Assembler.h
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <assert.h>
#include <string.h>

#include "..\Onegin\TextSort.h"
#include "..\general\Errors.h"

#include "Commands.h"


//{--------------------------------------------------------Assembler-Consts----------------------------------------------------------------

const  int MAX_TOKEN_LENGTH 	 = 64;
const  int MAX_ARG_LENGTH     	 = 32;
const  int MAX_LABEL_NAME_LENGTH = 64;
const  int MAX_COMMAND_LENGTH    = 32;

const  int PASSES = 2;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Globals-(for-a-better-future)---------------------------------------------------

static int CUR_STR_N = 0;
static int CUR_IP    = 0;   
static int CUR_PASS  = 1;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Compilation-Warnings-Logs-------------------------------------------------------

#define RET_COMPILATION_ERROR(ERROR_NAME, TOKEN) {					\
																	\
  	if (CUR_PASS == PASSES)											\
		LOG_COMPILATION_ERROR(ERROR_NAME, TOKEN);					\
																	\
	return ERROR_NAME;												\
}																	\
																	\
do {																\
																	\
} while (0)


#define LOG_COMPILATION_ERROR(ERROR_NAME, TOKEN) {					\
																	\
	WARNING_LOG(ERROR_NAME, ERROR);									\
																	\
	fprintf(stderr, "%8d | %s\n", CUR_STR_N + 1, TOKEN);			\
	printf("         | ^");											\
																	\
	for (int i = 0; i < strlen(TOKEN) - 1; ++i) 					\
		printf("~");												\
																	\
	printf("\n");													\
}																	\
																	\
do {																\
																	\
} while (0)

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Label-Fuxups-Structs------------------------------------------------------------

typedef struct label_t {
	
	char        name[MAX_LABEL_NAME_LENGTH] = "";
	Argument_t  jumpPoint                   = 0;

} Label_t;


struct FIXUPS_T {

	label_t* labelsList  = nullptr;
	size_t   labelsCount = 0;

} static FIXUPS;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------WRITE-Macros--------------------------------------------------------------------

#define WRITE(file, format, value) {  		\
											\
	if (CUR_PASS == PASSES) 				\
		fprintf(file, format, value);		\
}											\
											\
do {										\
											\
} while (0)

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Preprocessing-------------------------------------------------------------------


/**
 * @brief          Removes commentaries from the code
 *
 * @param[in,out]  sourceCode  The source code file
 *
 * @return         The error's code
 */
ERROR_CODES StripCode(File* sourceCode);


/**
 * @brief      Creates an executable file
 *
 * @param[in]  sourceFile  The source file
 *
 * @return     File (executable) pointer 
 */
FILE* CreateExecutable(const char* sourceFile);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Main-Compilation-Funcions-------------------------------------------------------

 
/**
 * @brief      Compiles source file into machine codes
 *
 * @param[in]  sourceCode  The source code file pointer
 *
 * @return     The error's code
 */
ERROR_CODES Compile(File* sourceCode);


/**
 * @brief           Compiles specific token
 *
 * @param[in]       currentStr      The current string ptr
 * @param[in,out]   executableFile  The executable file ptr
 *
 * @return          The error's code
 */
ERROR_CODES CompileToken(char* currentStr, FILE* executableFile);


/**
 * @brief      		Compile separate string
 *
 * @param[in]       currentStr      The current string ptr
 * @param[in,out]   executableFile  The executable file ptr
 *
 * @return     		The error's code
 */
ERROR_CODES ComipleString(char* currentStr, FILE* executableFile);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Working-With-Labels-Funcs-------------------------------------------------------


/**
 * @brief      		Updates labels list (in FIXUPS)
 *
 * @param[in,out]   labelName  The label name
 *
 * @return     		The error's code
 */
ERROR_CODES UpdateLables(char* labelName);


/**
 * @brief      Searches for the label
 *
 * @param[in]  labelName  The label name
 *
 * @return     Pointer to the label (nullptr if not found)
 */
Label_t* SearchLabel(char* labelName);


/**
 * @brief          Compiles a label (into machine codes)
 *
 * @param[in]      currentStr      The current string pointer
 * @param[in,out]  executableFile  The executable file
 *
 * @return         The error's code
 */
ERROR_CODES CompileLabel(char* currentStr, FILE* executableFile);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Working-With-Strings------------------------------------------------------------


/**
 * @brief      Counts the number of specific symbols in a string
 *
 * @param[in]  str     The string to search in
 * @param[in]  symbol  The symbol to search for
 *
 * @return     Number of symbols
 */
size_t StringCount(char* str, char symbol);


/**
 * @brief      Checks if the string is empty
 *
 * @param[in]  str   The string to check
 *
 * @return     The whether string is empty or not (bool)
 */
bool StringIsEmpty(char* str);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Arg-Types-Compiles--------------------------------------------------------------


/**
 * @brief         Compiles argument (if command has it)
 *
 * @param[in]     currentStr      The current string
 * @param[in,out] commandNum      The command number
 * @param[in]     executableFile  The executable file
 *
 * @return        The error's code
 */
ERROR_CODES CompileArgument(char* currentStr, char commandNum, FILE* executableFile);


/**
 * @brief          Looks for register arguments specifcallly
 *
 * @param[in]      argument      The argument itself
 * @param[in,out]  argContainer  The container for the argument to fulfill
 *
 * @return     	   Argument bits increment
 */
Instruction_t CompileReg(char* argument, char* argContainer);


/**
 * @brief      Looks for ram arguments specifcallly
 *
 * @param[in]  argument  The argument itself
 *
 * @return     RAM bits increment
 */
Instruction_t CompileRam(char* argument);


/**
 * @brief          Looks for const arguments specifically
 *
 * @param[in]      argument      The argument itself
 * @param[in,out]  argContainer  The container for the argument to fulfill
 *
 * @return     	   Immediate const bits increment
 */
Instruction_t CompileConst(char* argument, char* argContainer);

//}----------------------------------------------------------------------------------------------------------------------------------------


#endif // ASSEMBLER_H
