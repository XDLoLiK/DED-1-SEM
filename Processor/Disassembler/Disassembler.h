/**
 * @file Disassembler.h
 */

#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H


#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "..\Commands.h"
#include "..\..\general\Errors.h"
#include "..\..\Onegin\TextSort.h"
#include "..\Processor\Processor.h"
#include "..\Assembler\Assembler.h"


const int MAX_OUTPUT_PATH_SIZE = 256;


typedef struct disasm_info_t {

	size_t         codesSize  = 0;
	size_t 	  	   curIP 	  = 0;
	size_t    	   curPass    = 0;
	const size_t   PASSES     = 2;
	FILE*          disasmFile = nullptr;
	Instruction_t* codes  	  = nullptr;
	fixups_t	   FIXUPS     = {};

} Disasm_info_t;



/**
 * @brief      Decompiles a file
 *
 * @param      executablePath  The executable path
 *
 * @return     The error codes.
 */
ERROR_CODES Decompile(char* executablePath);



/**
 * @brief      Creates an out file
 *
 * @param[in]  sourcePath  The source path
 *
 * @return     out file ptr
 */
FILE* CreateOutFile(const char* sourcePath);




/**
 * @brief      Checks signature and version
 *
 * @param      DisassemblyInfo  The disassembly information
 *
 * @return     The error codes.
 */
ERROR_CODES CheckSignature(Disasm_info_t* DisassemblyInfo);



/**
 * @brief      Prints a label.
 *
 * @param      DisassemblyInfo  The disassembly information
 *
 * @return     The error codes.
 */
ERROR_CODES WriteLabel(Disasm_info_t* DisassemblyInfo);



/**
 * @brief      Prints an argument.
 *
 * @param[in]  instruction      The instruction
 * @param      DisassemblyInfo  The disassembly information
 *
 * @return     The error codes.
 */
ERROR_CODES WriteArgument(Instruction_t instruction, Disasm_info_t* DisassemblyInfo);



/**
 * @brief      Prints an instruction
 *
 * @param[in]  instruction      The instruction
 * @param      DisassemblyInfo  The disassembly information
 *
 * @return     The error codes.
 */
ERROR_CODES WriteInstruction(const char* instruction, Disasm_info_t* DisassemblyInfo);


/**
 * @brief      Reads codes
 *
 * @param      DisassemblyInfo  The disassembly information
 * @param[in]  executablePath   The executable path
 *
 * @return     The error's code
 */
ERROR_CODES ReadCodes(Disasm_info_t* DisassemblyInfo, char* executablePath);


/**
 * @brief      Decompiles a single string
 *
 * @param      DisassemblyInfo  The disassembly information
 *
 * @return     The error's code
 */
ERROR_CODES WriteString(Disasm_info_t* DisassemblyInfo);


/**
 * @brief      Finds a label
 *
 * @param      DisassemblyInfo  The disassembly information
 *
 * @return     label_t pointer
 */
Label_t* FindLabel(Disasm_info_t* DisassemblyInfo);


/**
 * @brief      Appends labels
 *
 * @param      DisassemblyInfo  The disassembly information
 *
 * @return     The error's code
 */
ERROR_CODES AppendLabels(Disasm_info_t* DisassemblyInfo);


/**
 * @brief      Handles the instrucrion
 *
 * @param[in]  command          The command
 * @param[in]  cmdNum           The command number
 * @param[in]  argsType         The arguments type
 * @param[in]  DisassemblyInfo  The disassembly information
 *
 * @return     The error's code
 */
ERROR_CODES HandleInstruction(const char* command, Instruction_t cmdNum, int argsType, Disasm_info_t* DisassemblyInfo);


#endif // DIDASSEMBLER_H
