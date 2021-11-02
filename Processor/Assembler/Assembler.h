/**
 * @file Assembler.h
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <assert.h>
#include <string.h>
#include <time.h>

#include "..\..\Onegin\TextSort.h"
#include "..\..\general\Errors.h"
#include "..\Commands.h"


//{--------------------------------------------------------Assembler-Consts----------------------------------------------------------------

const int MAX_TOKEN_LENGTH	 	 = 64;
const int MAX_ARG_LENGTH     	 = 32;
const int MAX_LABEL_NAME_LENGTH  = 64;
const int MAX_COMMAND_LENGTH     = 32;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Assembly-info-struct------------------------------------------------------------


/**
 * @brief      Gathers all the compilation info
 */
typedef struct asm_info_t {
	
	size_t 	  	   curIP 	 = 0;	 
	size_t	  	   curStr 	 = 0;
	size_t    	   curPass   = 1;
	const size_t   PASSES    = 2;
	Instruction_t* codes  	 = nullptr;
	bool           hasErrors = false;

} Asm_info_t;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Compilation-Warnings-Logs-------------------------------------------------------

#define RET_COMPILATION_ERROR(ERROR_NAME, TOKEN) {					\
																	\
  	if (AssemblyInfo->curPass == AssemblyInfo->PASSES) {			\
		LOG_COMPILATION_ERROR(ERROR_NAME, TOKEN);					\
	}																\
																	\
	return ERROR_NAME;												\
}																	\
																	\
do {																\
																	\
} while (0)


#define LOG_COMPILATION_ERROR(ERROR_NAME, TOKEN) {							\
																			\
	WARNING_LOG(ERROR_NAME, ERROR);											\
																			\
	AssemblyInfo->hasErrors = true;											\
																			\
	fprintf(stderr, "%8llu | %s\n", AssemblyInfo->curStr + 1, TOKEN);		\
	printf("         | ^");													\
																			\
	for (size_t letter = 0; letter < strlen(TOKEN) - 1; ++letter)		 	\
		printf("~");														\
																			\
	printf("\n");															\
}																			\
																			\
do {																		\
																			\
} while (0)

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Label-Fixups-Structs------------------------------------------------------------

typedef struct label_t {
	
	char        name[MAX_LABEL_NAME_LENGTH] = "";
	Argument_t  jumpPoint                   = 0;

} Label_t;


struct fixups_t {

	label_t* labelsList  		= (label_t*) calloc(100, sizeof (label_t));
	size_t   labelsCapacity		= 100;
	size_t   labelsCount 		= 0;

} static FIXUPS;

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
 * @brief      		Creates an executable file
 *
 * @param[in]  		sourceFile         The source file
 * @param[in,out]   AssemblyInfo       The assembly info struct pointer
 *
 * @return     		File (executable) pointer
 */
FILE* CreateExecutable(const char* sourceFile, Asm_info_t* AssemblyInfo);

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
 * @brief           Compiles instruction and its argument (if it has one)
 *
 * @param[in]       currentStr       The current string ptr
 * @param[in,out]   AssemblyInfo     The assembly info struct pointer
 *
 * @return          The error's code
 */
ERROR_CODES CompileInstruction(char* currentStr, Asm_info_t* AssemblyInfo);


/**
 * @brief      		Compile separate string
 *
 * @param[in]       currentStr      The current string ptr
 * @param[in,out]   AssemblyInfo    The assembly info struct pointer 
 *
 * @return     		The error's code
 */
ERROR_CODES ComipleString(char* currentStr, Asm_info_t* AssemblyInfo);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Working-With-Labels-Funcs-------------------------------------------------------


/**
 * @brief         Updates labels list (in FIXUPS)
 *
 * @param[in,out] labelName     The label name
 * @param         AssemblyInfo  The assembly info struct pointer
 *
 * @return        The error's code
 */
ERROR_CODES UpdateLables(char* labelName, Asm_info_t* AssemblyInfo);


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
 * @param[in]      labelName        The name of the label
 * @param[in,out]  AssemblyInfo     The assembly info struct pointer
 * 
 * @return         The error's code
 */
ERROR_CODES CompileLabel(char* labelName, Asm_info_t* AssemblyInfo);

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
 * @param[in]     argument        The argument string
 * @param[in,out] commandNum      The command number
 * @param[in,out] AssemblyInfo    The assembly info struct pointer
 *
 * @return        The error's code
 */
ERROR_CODES CompileArgument(char* argument, char commandNum, Asm_info_t* AssemblyInfo);


/**
 * @brief         Looks for register arguments specifcallly
 *
 * @param[in]     argument      The argument itself
 * @param[in,out] argContainer  The container of the argument value
 * @param         AssemblyInfo  The assembly info struct pointer
 *
 * @return        The error's code
 */
ERROR_CODES CompileReg(char* argument, Argument_t* argContainer, Asm_info_t* AssemblyInfo);


/**
 * @brief      Looks for ram arguments specifcallly
 *
 * @param[in]  argument      The argument itself
 * @param      AssemblyInfo  The assembly info struct pointer
 *
 * @return     whether it is RAM arg or not (bool)
 */
bool IsRam(char* argument, Asm_info_t* AssemblyInfo);


/**
 * @brief         Looks for const arguments specifically
 *
 * @param[in]     argument      The argument itself
 * @param[in,out] argContainer  The container of the argument value
 * @param         AssemblyInfo  The assembly info struct pointer
 *
 * @return        The error's code
 */
ERROR_CODES CompileConst(char* argument, Argument_t* argContainer, Asm_info_t* AssemblyInfo);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Add-To-The-List-Functions-------------------------------------------------------


/**
 * @brief     	 	Adds an argument_t value to the codes list
 *
 * @param[in]  		argument      The argument value
 * @param[in,out]   AssemblyInfo  General assembly information
 */
void AddArgument(Argument_t argument, Asm_info_t* AssemblyInfo);


/**
 * @brief     	 	Adds an instruction_t value to the codes list
 *
 * @param[in]  		cmdNum        The command number
 * @param[in,out]	AssemblyInfo  General assembly information
 */
void AddInstruction(Instruction_t cmdNum, Asm_info_t* AssemblyInfo);

//}----------------------------------------------------------------------------------------------------------------------------------------


#endif // ASSEMBLER_H
