/**
 * @file Assembler.cpp
 */


#include "Assembler.h"

	
#define DEF_CMD(cmd, num, args, ...)									\
																		\
	else if (strcmp(token, #cmd) == 0)			 	 					\
			fprintf(executableFile, "\t%08X\n", (int) CMD_##cmd);		
		


// TODO: CompilePush
// TODO: CompileLabel
// TODO: CompilePop
// TODO: SearchLabel
// TODO: UpdateFixups


//{--------------------------------------------------Main-Compilation-function-------------------------------------------------------------

ERROR_CODES Compile(File* sourceCode, FILE* executableFile)
{
	assert(sourceCode);
	assert(executableFile);

	StripCode(sourceCode); // deleting comments

	char token[MAX_TOKEN_LENGTH] = "";

	for (; CUR_STR < sourceCode->strings_n; CUR_STR++) {
		
		if (!IS_OK(GetToken(token, sourceCode->strings_list[CUR_STR].start)))
			continue; // GetToken(...) == EMPTY_STRING

		if (!IS_OK(HandleToken(token, executableFile)))
			continue; // LOG_COMPILATION_ERROR(...)
	}

	fclose(executableFile);

	RETURN(NO_ERROR);
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{------------------------------------------------Argumnets-Commands-Compilation----------------------------------------------------------

ERROR_CODES CompilePush(char* pushCommand, FILE* executableFile)
{
	assert(pushCommand);
	assert(executableFile);

	// int argsBits = 0;

	// char args[MAX_ARG_LENGTH]     = "";
	// char regArg[MAX_ARG_LENGTH]   = "";
	// char immConst[MAX_ARG_LENGTH] = "";

	// if (sscanf(pushCommand, "%*s %s[a-d+x[]1-9]", args) != 1)
	// 	ERROR_LOG(INAPPROPRIATE_ARGUMENT);

	// if (sscanf(args, "[%[a-d1-9+x]]") == 1)
	// 	argsBits += RAM_ARG; // 10000000

	// if (sscanf(args, " %1[a-d]x", toPrint) == 1) {
	// 	argsBits += REG_ARG;  // 01000000

	// }

	// if (sscanf(args, "%[1-9]")) {

	// }

	RETURN(NO_ERROR);
}


ERROR_CODES CompilePop(char* popCommand, FILE* executableFile)
{
	assert(popCommand);
	assert(executableFile);

	RETURN(NO_ERROR);
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Label-Handlers------------------------------------------------------------------

ERROR_CODES CompileLabel(char* labelName, FILE* executableFile)
{
	assert(labelName);
	assert(executableFile);

	Label_t* label = SearchLabel(labelName);

	if (label == nullptr) {
		// RETURN();
	}

	RETURN(NO_ERROR);
}


Label_t* SearchLabel(char* labelName)
{
	assert(labelName);

	for (int i = 0; i < FIXUPS.labelsCount; ++i) {

		if (FIXUPS.labelsList[i].name == labelName) 
			return &FIXUPS.labelsList[i];
	}

	UpdateLables(labelName);

	return &FIXUPS.labelsList[FIXUPS.labelsCount - 1];
}


ERROR_CODES UpdateLables(char* labelName)
{
	assert(labelName);

	Label_t* newptr = (Label_t*) realloc(FIXUPS.labelsList, (FIXUPS.labelsCount + 1) * sizeof (Label_t));

	if (newptr == nullptr) {
		RETURN(ALLOCATION_ERROR);
	}

	else {

		FIXUPS.labelsList = newptr;
		++FIXUPS.labelsCount;

		strcpy(FIXUPS.labelsList[FIXUPS.labelsCount - 1].name, labelName);
		FIXUPS.labelsList[FIXUPS.labelsCount - 1].jumpPoint = -1; 
	}

	RETURN(NO_ERROR);
}

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Token-Handler-------------------------------------------------------------------

ERROR_CODES HandleToken(char* token, FILE* executableFile)
{
	assert(token);
	assert(executableFile);

	if (strcmp(token, "push") == 0) {	
		RETURN(CompilePush(token, executableFile));				
	}

	else if (strcmp(token, "pop") == 0) {	
		RETURN(CompilePop(token, executableFile));				
	}			

	#include "defcmd.h" // -> 
	// else if (strcmp(token, ...) == 0) ... 															

	else if (IS_OK(CompileLabel(token, executableFile))) {
		RET_COMPILATION_ERROR(INAPPROPRIATE_LABEL, CUR_STR + 1, token);			
	}

	else {
		RET_COMPILATION_ERROR(INVALID_SYNTAX, CUR_STR + 1, token);
	}

	RETURN(NO_ERROR);
}


ERROR_CODES GetToken(char* token, char* buffer)
{
	assert(buffer);

	if (sscanf(buffer, " %s ", token) == 0)
		return EMPTY_STRING;

	RETURN(NO_ERROR); 
}

//}----------------------------------------------------------------------------------------------------------------------------------------


ERROR_CODES StripCode(File* sourceCode)
{
	assert(sourceCode);

	for (int i = 0; i < sourceCode->size_bytes; ++i) {
		
		if (sourceCode->text[i] == ';')
			sourceCode->text[i] = '\n';
	}

	RETURN(NO_ERROR);
}


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

