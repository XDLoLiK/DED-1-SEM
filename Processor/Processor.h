/**
 * @file Processor.h
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdio.h>
#include <assert.h>

#include "Commands.h"

#include "..\Stack\Stack.h"


const uint64_t MEM_SIZE = 524288; /// 512 MB in bytes
const uint64_t REGS_NUM = 4;	  /// 4 registers


//{--------------------------------------------------Typedefs-of-processor-fileds'-types---------------------------------------------------

typedef int32_t		VideoMem_t;
typedef int64_t		Reg_t;
typedef StackElem_t Codes_t;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{-----------------------------------------------------------Processor-struct-------------------------------------------------------------

typedef struct processor {

	VideoMem_t*  videomem 	    = nullptr;
	Codes_t* 	 codes 		 	= nullptr;      
	StackElem_t* ram 		    = nullptr;		 
	int64_t   	 ip 		    = -1;
	Stack_t   	 stack 		 	= {};
	StackElem_t  regs[REGS_NUM] = {};

} Processor;

//{----------------------------------------------------------------------------------------------------------------------------------------


typedef struct command_t {
	
} Command_t;


ERROR_CODES Execute(Processor* PROCESSOR);
ERROR_CODES ProcessorCtor(Processor* AMD_Ryzen, char* instructions);
void ProcessorDtor(Processor* IntelPentium);
ERROR_CODES ScanCodes(FILE* executableFile, Codes_t* codes);


#endif // PROCESSOR_H
