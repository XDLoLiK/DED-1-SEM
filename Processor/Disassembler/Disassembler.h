/**
 * @file Disassembler.h
 */

#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "..\Commands.h"
#include "..\..\general\Errors.h"
#include "..\..\Onegin\TextSort.h"


const int MAX_OUTPUT_PATH_SIZE = 256;


typedef struct disasm_info_t {

	size_t 	  	   curIP 	 = 0;
	size_t    	   curPass   = 0;
	const size_t   PASSES    = 2;
	Instruction_t* codes  	 = nullptr;

} Disasm_info_t;


ERROR_CODES Decompile(File* executableFile);
FILE* CreateOutFile(const char* sourcePath);
ERROR_CODES CheckExecutable(Disasm_info_t* DisassemblyInfo);

#endif // DIDASSEMBLER_H
