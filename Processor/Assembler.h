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


const  int MAX_TOKEN_LENGTH 		= 64;
const  int MAX_ARG_LENGTH     	= 32;
const  int MAX_LABEL_NAME_LENGTH = 64;

static int CUR_STR = 0;


//{--------------------------------------------------------Compilation-Warnings-Logs-------------------------------------------------------

#define RET_COMPILATION_ERROR(ERROR_NAME, STRING_N, TOKEN) {		\
																	\
	LOG_COMPILATION_ERROR(ERROR_NAME, STRING_N, TOKEN);				\
	return ERROR_NAME;												\
}																	\
																	\
do {																\
																	\
} while (0)


#define LOG_COMPILATION_ERROR(ERROR_NAME, STRING_N, TOKEN) {		\
																	\
	WARNING_LOG(ERROR_NAME);										\
																	\
	fprintf(stderr, "%8d | %s\n", STRING_N + 1, TOKEN);				\
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
	
	char name[MAX_LABEL_NAME_LENGTH] = "";
	char jumpPoint                   = 0;

} Label_t;


struct FIXUPS_T {

	label_t* labelsList  = nullptr;
	size_t   labelsCount = 0;

} static FIXUPS;

//}----------------------------------------------------------------------------------------------------------------------------------------


ERROR_CODES StripCode(File* sourceCode);
FILE* CreateExecutable(const char* sourcePath);
ERROR_CODES Compile(File* sourceCode, FILE* executableFile);
ERROR_CODES GetToken(char* token, char* buffer);
ERROR_CODES HandleToken(char* token, FILE* executableFile);
ERROR_CODES UpdateLables(char* labelName);
Label_t* SearchLabel(char* labelName);
ERROR_CODES CompileLabel(char* labelName, FILE* executableFile);
ERROR_CODES CompilePush(char* pushCommand, FILE* executableFile);
ERROR_CODES CompilePop(char* popCommand, FILE* executableFile);


#endif // ASSEMBLER_H
