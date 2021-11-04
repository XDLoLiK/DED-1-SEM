/**
 * @file Assembler.cpp
 */


#include "Assembler.h"


#define DEF_CMD(cmd, num, argsType, ...)								\
																		\
	else if (strcmp(token, #cmd) == 0) {						 		\
																		\
		if (argsType == NO_ARGS) {										\
			AddInstruction(CMD_##cmd, AssemblyInfo);					\
		}																\
																		\
		else if (argsType == LABEL_ARG) {								\
																		\
			AddInstruction(CMD_##cmd, AssemblyInfo);					\
																		\
			char labelName[MAX_LABEL_NAME_LENGTH] = "";					\
			sscanf(currentStr, "%*s %s", labelName);					\
																		\
			CompileLabel(labelName, AssemblyInfo);						\
		}																\
																		\
		else if (argsType  == MEMORY_ARG) {								\
																		\
			char argument[MAX_ARG_LENGTH] = "";							\
			sscanf(currentStr, "%*s %[^\n]", argument);					\
																		\
			CompileArgument(argument, CMD_##cmd, AssemblyInfo);			\
		}																\
																		\
		else RET_COMPILATION_ERROR(INAPPROPRIATE_COMMAND, #cmd);		\
	}
			

//{--------------------------------------------------Main-Compilation-functions-------------------------------------------------------------

ERROR_CODES Compile(File* sourceFile)
{
	assert(sourceFile);

	printf(">>> Compilation started ...\n");
	clock_t CompilationStart = clock();

	Asm_info_t AssemblyInfo = {};
	AssemblyInfo.codes      = (Instruction_t*) calloc(MAX_CODES_CAPACITY, 1);

	StripCode(sourceFile); // deleting comments
	
	for (; AssemblyInfo.curPass <= AssemblyInfo.PASSES; ++AssemblyInfo.curPass) {

		AssemblyInfo.curStr = 0;
		AssemblyInfo.curIP  = sizeof SIGNATURE + sizeof VERSION;

		for (; AssemblyInfo.curStr < sourceFile->strings_n; AssemblyInfo.curStr++) {
			ComipleString(sourceFile->strings_list[AssemblyInfo.curStr].start, &AssemblyInfo);
		}
	}

	if (AssemblyInfo.hasErrors == false) {

		FILE* executableFile = CreateExecutable(sourceFile->path, &AssemblyInfo);
		
		fwrite(AssemblyInfo.codes, AssemblyInfo.curIP, sizeof (char), executableFile);
		fclose(executableFile);
	} 

	else {
		return COMPILATION_ERROR;
	}

	clock_t CompilationEnd  = clock();
	double  CompilationTime = (double) (CompilationEnd - CompilationStart) / CLOCKS_PER_SEC;

	printf(">>> Compilatoin finished in %g\n", CompilationTime);

	RETURN(NO_ERROR);
}


ERROR_CODES ComipleString(char* currentStr, Asm_info_t* AssemblyInfo)
{
	assert(currentStr);
	assert(AssemblyInfo);

	char token[MAX_TOKEN_LENGTH] = "";

	if (StringIsEmpty(currentStr)) {
		return EMPTY_STRING;
	}
	
	sscanf(currentStr, " %[^\n]", token);

	if (strchr(token, ':') != nullptr) {

		if (SearchLabel(token, AssemblyInfo) == nullptr) {
			UpdateLables(token, AssemblyInfo);
		}
	}

	else if (IS_OK(CompileInstruction(currentStr, AssemblyInfo))) {
		RETURN(NO_ERROR);
	}

	else {
		RET_COMPILATION_ERROR(INVALID_SYNTAX, token);
	}

	RETURN(NO_ERROR);
}


//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Label-Handlers------------------------------------------------------------------

ERROR_CODES CompileLabel(char* labelName, Asm_info_t* AssemblyInfo)
{
	assert(labelName);
	assert(AssemblyInfo);

	Label_t* label = SearchLabel(labelName, AssemblyInfo);

	if (label != nullptr) {
		AddArgument(label->jumpPoint, AssemblyInfo);
	}

	else {

		if (AssemblyInfo->curPass >= AssemblyInfo->PASSES) {
			RET_COMPILATION_ERROR(INAPPROPRIATE_LABEL, labelName);
		}

		else {
			AddArgument(-1, AssemblyInfo);
		}
	}

	RETURN(NO_ERROR);
}


Label_t* SearchLabel(char* labelName, Asm_info_t* AssemblyInfo)
{
	assert(labelName);

	for (size_t i = 0; i < AssemblyInfo->FIXUPS.labelsCount; ++i) {

		if (strcmp(AssemblyInfo->FIXUPS.labelsList[i].name, labelName) == 0) {
			return &AssemblyInfo->FIXUPS.labelsList[i];
		}
	}

	return nullptr;
}


ERROR_CODES UpdateLables(char* labelName, Asm_info_t* AssemblyInfo)
{
	assert(labelName);
	assert(AssemblyInfo);

	labelName[strlen(labelName) - 1] = '\0';

	if (AssemblyInfo->FIXUPS.labelsCount >= AssemblyInfo->FIXUPS.labelsCapacity) {

		Label_t* newptr = (Label_t*) realloc(AssemblyInfo->FIXUPS.labelsList, (AssemblyInfo->FIXUPS.labelsCapacity + 10) * sizeof (Label_t));

		if (newptr == nullptr) {
			RETURN(ALLOCATION_ERROR);
		}

		else {
			AssemblyInfo->FIXUPS.labelsList = newptr;
		}	
	}

	AssemblyInfo->FIXUPS.labelsCount += 1;

	strcpy(AssemblyInfo->FIXUPS.labelsList[AssemblyInfo->FIXUPS.labelsCount - 1].name, labelName);
	AssemblyInfo->FIXUPS.labelsList[AssemblyInfo->FIXUPS.labelsCount - 1].jumpPoint = AssemblyInfo->curIP;

	RETURN(NO_ERROR);
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Various-Argument-Types-Handlers-------------------------------------------------

ERROR_CODES CompileInstruction(char* currentStr, Asm_info_t* AssemblyInfo)
{
	assert(currentStr);
	assert(AssemblyInfo);

	char token[MAX_TOKEN_LENGTH] = "";

	if (sscanf(currentStr, " %[a-zA-Z]", token) != 1)  {
		RET_COMPILATION_ERROR(INVALID_TOKEN, token);
	}

	#include "..\DEF_CMD.h" // -> 
	// else if (strcmp(token, ...) == 0) ... 															

	else {
		return INVALID_SYNTAX;
	}

	RETURN(NO_ERROR);
}


ERROR_CODES CompileArgument(char* argument, char commandNum, Asm_info_t* AssemblyInfo)
{
	assert(argument);
	assert(AssemblyInfo);

	size_t commandPointer = AssemblyInfo->curIP;
	AssemblyInfo->curIP += sizeof (Instruction_t);

	int argBits = 0;

	// RAM ARG HANDLER

	if (IsRam(argument, AssemblyInfo)) {
		argBits += RAM_ARG;
	}

	// REG ARG HANDLER

	Argument_t regArg = (Argument_t) NEUTRAL;
	CompileReg(argument, &regArg, AssemblyInfo);

	if (regArg != (Argument_t) NEUTRAL) {
		argBits += REG_ARG;
		AddArgument(regArg, AssemblyInfo);
	}

	// IMMEDIATE CONST HANDLER

	Argument_t immConst = (Argument_t) NEUTRAL;
	CompileConst(argument, &immConst, AssemblyInfo);

	if (immConst != (Argument_t) NEUTRAL) {
		argBits += IMM_CONST;
		AddArgument(immConst, AssemblyInfo);
	}

	* (Instruction_t*) (AssemblyInfo->codes + commandPointer) = (Instruction_t) (commandNum + argBits);

	RETURN(NO_ERROR);
}


bool IsRam(char* argument, Asm_info_t* AssemblyInfo)
{
	assert(argument);

	if (strchr(argument, ']') > strchr(argument, '[')) {

		if (StringCountChar(argument, '[') == 1 && StringCountChar(argument, ']') == 1) {
			return true;
		}
		
		else {
			LOG_COMPILATION_ERROR(INAPPROPRIATE_ARGUMENT, argument);
			return false;
		}
	}

	return false;
}


ERROR_CODES CompileReg(char* argument, Argument_t* argContainer, Asm_info_t* AssemblyInfo)
{
	assert(argument);
	assert(argContainer);
	
	int i = 0;

	while (argument[i] != '\0') {

		if (argument[i] - 'a' >= 0) {

			if (argument[i + 1] == 'x') {

				*argContainer = (Argument_t) (argument[i] - 'a');	
				RETURN(NO_ERROR);
			}

			else {
				RET_COMPILATION_ERROR(INAPPROPRIATE_ARGUMENT, argument);
			}
		}

		i++;
	}

	RETURN(NO_ERROR);
}


ERROR_CODES CompileConst(char* argument, Argument_t* argContainer, Asm_info_t* AssemblyInfo)
{
	assert(argument);
	assert(argContainer);

	int i = 0;

	while (argument[i] != '\0') {

		if (argument[i] - '0' < 10 && argument[i] - '0' >= 0) {
			
			if (sscanf(&argument[i], "%lld", argContainer) != 1) {
				RET_COMPILATION_ERROR(INAPPROPRIATE_ARGUMENT, argument);
			}
			
			else {
				RETURN(NO_ERROR);
			}
		}

		i++;
	}

	RETURN(NO_ERROR);
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Preprocessing-Functions---------------------------------------------------------

FILE* CreateExecutable(const char* sourcePath, Asm_info_t* AssemblyInfo)
{
	assert(sourcePath);
	assert(AssemblyInfo);

	char outputPath[MAX_PATH_SIZE] = "";		

	strcpy(outputPath, sourcePath);				
	outputPath[strlen(outputPath) - 3] = '\0';	
	
	strcat(outputPath, "cum");					

	FILE* executableFile = fopen(outputPath, "wb");
	
	* (Signature_t*) (AssemblyInfo->codes) = SIGNATURE;
	AssemblyInfo->curIP += sizeof (Signature_t);

	* (Version_t*)   (AssemblyInfo->codes + sizeof SIGNATURE) = VERSION;
	AssemblyInfo->curIP += sizeof (Version_t);

	return executableFile;
}


ERROR_CODES StripCode(File* sourceFile)
{
	assert(sourceFile);

	for (size_t i = 0; i < sourceFile->size_bytes; ++i) {
		
		if (sourceFile->text[i] == ';') {
			sourceFile->text[i] = '\n';
		}
	}

	RETURN(NO_ERROR);
}

//{----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------String-Functions----------------------------------------------------------------

size_t StringCountChar(char* str, char symbol)
{
	assert(str);

	size_t count = 0;

	for (size_t i = 0; i < strlen(str); ++i) {

		if (str[i] == '\0') {
			break;
		}

		else if (str[i] == symbol) {
			++count;
		}
	}

	return count;
}


bool StringIsEmpty(char* str)
{
	assert(str);

	while (*str++ != '\n') {

		if (*str != '\t' && *str != ' ') {
			return false;
		}
	}

	return true;
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Add-To-The-List-Functions-------------------------------------------------------

void AddInstruction(Instruction_t cmdNum, Asm_info_t* AssemblyInfo)
{
	assert(AssemblyInfo);

	* (Instruction_t*) (AssemblyInfo->codes + AssemblyInfo->curIP) = (Instruction_t) cmdNum;
	AssemblyInfo->curIP += sizeof (Instruction_t);
}


void AddArgument(Argument_t argument, Asm_info_t* AssemblyInfo)
{
	assert(AssemblyInfo);

	* (Argument_t*) (AssemblyInfo->codes + AssemblyInfo->curIP) = (Argument_t) argument;
	AssemblyInfo->curIP += sizeof (Argument_t);
}

//}----------------------------------------------------------------------------------------------------------------------------------------
