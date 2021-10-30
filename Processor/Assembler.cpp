/**
 * @file Assembler.cpp
 */


#include "Assembler.h"

	
#define DEF_CMD(cmd, num, args, ...)									\
																		\
	else if (strcmp(token, #cmd) == 0) {				 				\
																		\
		if (args == 0) {												\
			WRITE(executableFile, "%08X\n", CMD_##cmd);					\
			CUR_IP += sizeof (Instruction_t);							\
		}																\
																		\
		else if (args == 1) {											\
			WRITE(executableFile, "%08X ", CMD_##cmd);					\
			CUR_IP += sizeof (Instruction_t);							\
																		\
			CompileLabel(currentStr, executableFile);					\
		}																\
																		\
		else if (args == 2) {											\
			CompileArgument(currentStr, CMD_##cmd, executableFile);		\
		}																\
	}
			

//{--------------------------------------------------Main-Compilation-functions-------------------------------------------------------------

ERROR_CODES Compile(File* sourceFile)
{
	assert(sourceFile);

	FILE* executableFile = CreateExecutable(sourceFile->path);
	StripCode(sourceFile); // deleting comments

	char  token[MAX_TOKEN_LENGTH] = "";
	
	for (; CUR_PASS <= PASSES; ++CUR_PASS) {
		
		CUR_STR_N = 0;
		CUR_IP    = 0;

		for (; CUR_STR_N < sourceFile->strings_n; CUR_STR_N++) 
			ComipleString(sourceFile->strings_list[CUR_STR_N].start, executableFile);
	}

	fclose(executableFile);

	RETURN(NO_ERROR);
}


ERROR_CODES ComipleString(char* currentStr, FILE* executableFile)
{
	assert(currentStr);
	assert(executableFile);

	char token[MAX_TOKEN_LENGTH] = "";

	if (StringIsEmpty(currentStr))
		return EMPTY_STRING;
	
	sscanf(currentStr, " %[^\n]", token);

	if (token[strlen(token) - 1] == ':') {

		if (SearchLabel(token) == nullptr) 
			UpdateLables(token);
	}

	else if (IS_OK(CompileToken(currentStr, executableFile))) {
		RETURN(NO_ERROR);
	}

	else {
		RET_COMPILATION_ERROR(INVALID_SYNTAX, token);
	}

	RETURN(NO_ERROR);
}
        

ERROR_CODES StripCode(File* sourceFile)
{
	assert(sourceFile);

	for (int i = 0; i < sourceFile->size_bytes; ++i) {
		
		if (sourceFile->text[i] == ';')
			sourceFile->text[i] = '\n';
	}

	RETURN(NO_ERROR);
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Label-Handlers------------------------------------------------------------------

ERROR_CODES CompileLabel(char* currentStr, FILE* executableFile)
{
	assert(currentStr);
	assert(executableFile);

	char labelName[MAX_LABEL_NAME_LENGTH] = "";

	sscanf(currentStr, "%*s %s", labelName);

	Label_t* label = SearchLabel(labelName);

	if (label != nullptr) {

		WRITE(executableFile, "%08X\n", label->jumpPoint);
		CUR_IP += sizeof (Argument_t);
	}

	else if (CUR_PASS >= 2) {
		RET_COMPILATION_ERROR(INAPPROPRIATE_LABEL, labelName);
	}

	else {
		WRITE(executableFile, "%08X\n", -1);
		CUR_IP += sizeof (Argument_t);
	}

	RETURN(NO_ERROR);
}


Label_t* SearchLabel(char* labelName)
{
	assert(labelName);

	for (int i = 0; i < FIXUPS.labelsCount; ++i) {

		if (strcmp(FIXUPS.labelsList[i].name, labelName) == 0) 
			return &FIXUPS.labelsList[i];
	}

	return nullptr;
}


ERROR_CODES UpdateLables(char* labelName)
{
	assert(labelName);

	labelName[strlen(labelName) - 1] = '\0';

	Label_t* newptr = (Label_t*) realloc(FIXUPS.labelsList, (FIXUPS.labelsCount + 1) * sizeof (Label_t));

	if (newptr == nullptr) {

		RETURN(ALLOCATION_ERROR);
	}

	else {

		FIXUPS.labelsList = newptr;
		++FIXUPS.labelsCount;

		strcpy(FIXUPS.labelsList[FIXUPS.labelsCount - 1].name, labelName);
		FIXUPS.labelsList[FIXUPS.labelsCount - 1].jumpPoint = CUR_IP;
	}

	RETURN(NO_ERROR);
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Various-Types-Compiler----------------------------------------------------------

ERROR_CODES CompileToken(char* currentStr, FILE* executableFile)
{
	assert(currentStr);
	assert(executableFile);

	char token[MAX_TOKEN_LENGTH] = "";

	if (sscanf(currentStr, " %[a-zA-Z]", token) != 1)  {
		RET_COMPILATION_ERROR(INVALID_TOKEN, token);
	}

	#include "DEF_CMD.h" // -> 
	// else if (strcmp(token, ...) == 0) ... 															

	else 
		return INVALID_SYNTAX;

	RETURN(NO_ERROR);
}


ERROR_CODES CompileArgument(char* currentStr, char commandNum, FILE* executableFile)
{
	assert(currentStr);
	assert(executableFile);

	Instruction_t argBits = 0;
	Instruction_t result  = 0;

	char argument[MAX_ARG_LENGTH] = "";
	char regArg  [MAX_ARG_LENGTH] = "";
	char immConst[MAX_ARG_LENGTH] = "";

	sscanf(currentStr, "%*s %[^\n]", argument);

	if (result = CompileRam(argument)) 
		argBits += result;

	if (result = CompileReg(argument, regArg)) {

		argBits += result;
		CUR_IP  += sizeof (Argument_t);
	}

	if (result = CompileConst(argument, immConst)) {

		argBits += result;
		CUR_IP  += sizeof (Argument_t);
	}

	WRITE(executableFile, "%08X", commandNum + argBits);
	CUR_IP += 1;

	if (strlen(immConst))
		WRITE(executableFile, " %08X", strtoll(immConst, nullptr, 10));

	if (strlen(regArg))
		WRITE(executableFile, " %08X", *regArg - 'a');

	WRITE(executableFile, "\n", 0);

	RETURN(NO_ERROR);
}


Instruction_t CompileRam(char* argument)
{
	assert(argument);

	if (strchr(argument, ']') > strchr(argument, '[')) {

		if (StringCount(argument, '[') == 1 && StringCount(argument, ']') == 1) 
			return RAM_ARG;
		
		else
			RET_COMPILATION_ERROR(INAPPROPRIATE_ARGUMENT, argument);
	}

	return 0;
}


Instruction_t CompileReg(char* argument, char* argContainer)
{
	assert(argument);
	assert(argContainer);
	
	int i = 0;

	while (argument[i] != '\0') {

		if (argument[i] - 'a' >= 0 && argument[i] - 'a' <= 3) {

			if (argument[i + 1] == 'x') {

				*argContainer = argument[i];	
				return REG_ARG;
			}

			else {
				RET_COMPILATION_ERROR(INAPPROPRIATE_ARGUMENT, argument);
			}
		}

		i++;
	}

	return 0;
}


Instruction_t CompileConst(char* argument, char* argContainer)
{
	assert(argument);
	assert(argContainer);

	int i = 0;

	while (argument[i] != '\0') {

		if (argument[i] - '0' < 10 && argument[i] - '0' >= 0) {
			
			sscanf(&argument[i], "%[0-9]", argContainer);
			return IMM_CONST;
		}

		i++;
	}

	return 0;
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------No-Name-LOL---------------------------------------------------------------------

FILE* CreateExecutable(const char* sourcePath)
{
	assert(sourcePath);

	char outputPath[MAX_PATH_SIZE] = "";		// | Output path variable
	strcpy(outputPath, sourcePath);				// | Copying source path there
	outputPath[strlen(outputPath) - 3] = '\0';	// | cutting off the .ass part
	strcat(outputPath, "cum");					// | setting the extention to .cum


	FILE* executableFile = fopen(outputPath, "w");				// | creating <name>.cum
	fprintf(executableFile, "%s %lg\n", SIGNATURE, VERSION);	// | putting signature and version there

	return executableFile;
}


size_t StringCount(char* str, char symbol)
{
	assert(str);

	size_t count = 0;

	for (int i = 0; i < strlen(str); ++i) {

		if (str[i] == '\0')
			break;

		else if (str[i] == symbol)
			++count;
	}

	return count;
}


bool StringIsEmpty(char* str)
{
	assert(str);

	while (*str++ != '\n') {

		if (*str != '\t' && *str != ' ')
			return false;
	}

	return true;
}

//}----------------------------------------------------------------------------------------------------------------------------------------
