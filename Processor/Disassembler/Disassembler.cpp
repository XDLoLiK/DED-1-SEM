/**
 * @file Disassembler.cpp
 */

#include "Disassembler.h"


#define DEF_CMD(cmd, num, argsType, ...) {      							\
																			\
	case (CMD_##cmd):														\
																			\
		HandleInstruction(#cmd, CMD_##cmd, argsType DisassemblyInfo);		\
		break;																\
}


ERROR_CODES Decompile(char* executablePath)
{
	assert(executablePath);

	printf(">>> Decompilation started ...\n");

	clock_t DecompilationStart = clock();

	Disasm_info_t DisassemblyInfo = {};
	
	if (!IS_OK(ReadCodes(&DisassemblyInfo, executablePath))) {
		return DECOMPILATION_ERROR;
	}

	if (!IS_OK(CheckExecutable(&DisassemblyInfo))) {
		return DECOMPILATION_ERROR;
	}

	DisassemblyInfo.disasmFile = CreateOutFile(executablePath);

	for (; DisassemblyInfo.curPass < DisassemblyInfo.PASSES; ++DisassemblyInfo.curPass) {

		DisassemblyInfo.curIP = sizeof SIGNATURE + sizeof VERSION;

		while (DisassemblyInfo.curIP < DisassemblyInfo.codesSize) {
			WriteString(&DisassemblyInfo);
		}
	}

	fclose(DisassemblyInfo.disasmFile);

	clock_t DecompilationEnd  = clock();
	double  DecompilationTime = (double) (DecompilationEnd - DecompilationStart) / CLOCKS_PER_SEC;

	printf(">>> Decompilation finished in %g\n", DecompilationTime);

	RETURN(NO_ERROR);
}


ERROR_CODES HandleInstruction(const char* command, int cmdNum, int argsType, Disasm_info_t* DisassemblyInfo)
{
	assert(command);
	assert(DisassemblyInfo);

	if (argsType == NO_ARGS) {							
		WriteInstruction(command, DisassemblyInfo);		
		fprintf(DisassemblyInfo->disasmFile, "\n");		
	}													
															
	else if (argsType == LABEL_ARG) {					
		WriteInstruction(command, DisassemblyInfo);		
		AppendLabels(DisassemblyInfo);					
	}													
															
	else if (argsType == MEMORY_ARG) {					
		WriteInstruction(command, DisassemblyInfo);		
		WriteArgument(cmdNum, DisassemblyInfo);    	
	}

	RETURN(NO_ERROR);													
}


ERROR_CODES WriteString(Disasm_info_t* DisassemblyInfo)
{
	assert(DisassemblyInfo);
	
	Label_t* label = FindLabel(DisassemblyInfo);

	if (label != nullptr) {
		WriteLabel(DisassemblyInfo);	
	} 

	switch (DisassemblyInfo->codes[DisassemblyInfo->curIP]) {

		#include "..\DEF_CMD.h" //->
		// case (CMD_##cmd): ...

		default:
			RETURN(INAPPROPRIATE_COMMAND);
	}

	RETURN(NO_ERROR);
}


Label_t* FindLabel(Disasm_info_t* DisassemblyInfo)
{
	assert(DisassemblyInfo);

	for (size_t i = 0; i < DisassemblyInfo->FIXUPS.labelsCount; ++i) {
		
		if (DisassemblyInfo->FIXUPS.labelsList[i].jumpPoint == (long long) DisassemblyInfo->curIP) {
			return &DisassemblyInfo->FIXUPS.labelsList[i];
		}
	}

	return nullptr;
}


ERROR_CODES AppendLabels(Disasm_info_t* DisassemblyInfo)
{
	assert(DisassemblyInfo);

	if (DisassemblyInfo->FIXUPS.labelsCount >= DisassemblyInfo->FIXUPS.labelsCapacity) {

		Label_t* newptr = (Label_t*) realloc(DisassemblyInfo->FIXUPS.labelsList, (DisassemblyInfo->FIXUPS.labelsCapacity + 10) * sizeof (Label_t));

		DisassemblyInfo->FIXUPS.labelsCapacity += 10;

		if (newptr == nullptr) {
			RETURN(ALLOCATION_ERROR);
		}

		else {
			DisassemblyInfo->FIXUPS.labelsList = newptr;
		}	
	}

	DisassemblyInfo->FIXUPS.labelsCount += 1;

	char labelNum[MAX_LABEL_NAME_LENGTH] = "";
	itoa((int) DisassemblyInfo->FIXUPS.labelsCount, labelNum, 10);

	strcpy(DisassemblyInfo->FIXUPS.labelsList[DisassemblyInfo->FIXUPS.labelsCount - 1].name, labelNum);
	DisassemblyInfo->FIXUPS.labelsList[DisassemblyInfo->FIXUPS.labelsCount - 1].jumpPoint = DisassemblyInfo->curIP;

	DisassemblyInfo->curIP += sizeof (Argument_t);

	RETURN(NO_ERROR);
}


ERROR_CODES ReadCodes(Disasm_info_t* DisassemblyInfo, char* executablePath)
{
	assert(DisassemblyInfo);
	assert(executablePath);

	FILE* executableFile = fopen(executablePath, "rb");

	if (executableFile == nullptr) {
		RETURN(SCAN_ERROR);
	}

	else {
		DisassemblyInfo->codesSize = GetFileSize(executableFile);
	}

	DisassemblyInfo->codes = (Instruction_t*) calloc(DisassemblyInfo->codesSize, sizeof (Instruction_t));
	fread(DisassemblyInfo->codes, DisassemblyInfo->codesSize, sizeof (char), executableFile);

	fclose(executableFile);

	RETURN(NO_ERROR);
}


FILE* CreateOutFile(const char* sourcePath)
{
	assert(sourcePath);

	char outputPath[MAX_OUTPUT_PATH_SIZE] = "";		

	strcpy(outputPath, sourcePath);				
	outputPath[strlen(outputPath) - 4] = '\0';	
	
	strcat(outputPath, "*.ass");

	FILE* executableFile = fopen(outputPath, "w");
	
	return executableFile;
}


ERROR_CODES CheckExecutable(Disasm_info_t* DisassemblyInfo)
{
	assert(DisassemblyInfo);

	if (* (Signature_t*) (DisassemblyInfo->codes) != SIGNATURE) {
		RETURN(INAPPROPRIATE_SIGNATURE);
	} 

	else {
		fprintf(DisassemblyInfo->disasmFile, "%c ", SIGNATURE); 
	}

	if (* (Version_t*) (DisassemblyInfo->codes + sizeof SIGNATURE) != VERSION) {
		RETURN(INAPPROPRIATE_VERSION);
	} 

	else {
		fprintf(DisassemblyInfo->disasmFile, "%ld\n", (long) VERSION);
	}

	DisassemblyInfo->curIP += sizeof VERSION + sizeof SIGNATURE;

	RETURN(NO_ERROR);
}


ERROR_CODES WriteInstruction(const char* instruction, Disasm_info_t* DisassemblyInfo)
{
	assert(instruction);
	assert(DisassemblyInfo);

	fprintf(DisassemblyInfo->disasmFile, "%s ", instruction);
	DisassemblyInfo->curIP += sizeof (Instruction_t);

	RETURN(NO_ERROR);
}


ERROR_CODES WriteLabel(Disasm_info_t* DisassemblyInfo)
{
	assert(DisassemblyInfo);



	RETURN(NO_ERROR);
}


ERROR_CODES WriteArgument(Instruction_t instruction, Disasm_info_t* DisassemblyInfo)
{
	assert(DisassemblyInfo);

	if (instruction & RAM_ARG) {
		fprintf(DisassemblyInfo->disasmFile, "[ ");
	}

	if (instruction & REG_ARG) {

		fprintf(DisassemblyInfo->disasmFile, "%cx", 'a' + (char) DisassemblyInfo->codes[DisassemblyInfo->curIP]);
		DisassemblyInfo->curIP += sizeof (Argument_t);

		if (instruction & IMM_CONST) {

			fprintf(DisassemblyInfo->disasmFile, " + %ld", (long) DisassemblyInfo->codes[DisassemblyInfo->curIP]);
			DisassemblyInfo->curIP += sizeof (Argument_t);
		}
	}

	else if (instruction & IMM_CONST) {

		fprintf(DisassemblyInfo->disasmFile, "%ld", (long) DisassemblyInfo->codes[DisassemblyInfo->curIP]);
		DisassemblyInfo->curIP += sizeof (Argument_t);
	}

	if (instruction & RAM_ARG) {
		fprintf(DisassemblyInfo->disasmFile, " ]");
	}

	fprintf(DisassemblyInfo->disasmFile, "\n");

	RETURN(NO_ERROR);
}
