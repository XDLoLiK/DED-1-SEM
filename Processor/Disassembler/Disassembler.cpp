/**
 * @file Disassembler.cpp
 */

#include "Disassembler.h"


ERROR_CODES Decompile(File* executableFile)
{
	printf(">>> Decompilation started ...\n");

	clock_t DecompilationStart = clock();

	printf("OK\n");

	Disasm_info_t DisassemblyInfo = {};
	fread(DisassemblyInfo.codes, executableFile->size_bytes, sizeof (char), executableFile->file_ptr);

	printf("OK\n");

	printf("%s\n", DisassemblyInfo.codes);

	if (!IS_OK(CheckExecutable(&DisassemblyInfo))) {
		return DECOMPILATION_ERROR;
	} 

	printf("OK\n");

	FILE* disasmFile = CreateOutFile(executableFile->path);

	printf("OK\n");

	for (; DisassemblyInfo.curPass < DisassemblyInfo.PASSES; ++DisassemblyInfo.curPass) {

		//...
	}

	fwrite(DisassemblyInfo.codes, DisassemblyInfo.curIP, sizeof (char), disasmFile);
	fclose(disasmFile);

	clock_t DecompilationEnd  = clock();
	double  DecompilationTime = (double) (DecompilationEnd - DecompilationStart) / CLOCKS_PER_SEC;

	printf(">>> Decompilation finished in %g\n", DecompilationTime);

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

	if (* (Version_t*) (DisassemblyInfo->codes + sizeof (SIGNATURE)) != VERSION) {
		RETURN(INAPPROPRIATE_VERSION);
	}

	RETURN(NO_ERROR);
}
