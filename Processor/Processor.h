/**
 * @file Processor.h
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdio.h>
#include <assert.h>

#include "Commands.h"


// #include "C:\Users\Stas\Downloads\TX\TXLib.h"
#include "..\Stack\Stack.h"


const uint64_t MEM_SIZE = 524288; /// 512 MB in bytes
const uint64_t REGS_NUM = 4;	  /// 4 registers


//{--------------------------------------------------Typedefs-of-processor-fileds'-types---------------------------------------------------

typedef int32_t		VideoMem_t;
typedef StackElem_t	Reg_t;
typedef StackElem_t Ram_t;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------DSL-----------------------------------------------------------------------

#define STACK     PROCESSOR->stack
#define IP	 	  PROCESSOR->ip
#define CODES 	  PROCESSOR->codes
#define RAM       PROCESSOR->ram
#define REGS 	  PROCESSOR->regs
#define VIDEOMEM  PROCESSOR->videomem

#define PUSH(arg) StackPush(&STACK, (arg))
#define POP   	  StackPop (&STACK)
#define TOP       StackTop (&STACK)

//}----------------------------------------------------------------------------------------------------------------------------------------


//{-----------------------------------------------------------Processor-struct-------------------------------------------------------------

typedef struct processor {

	VideoMem_t*    videomem 	  = nullptr;
	Instruction_t* codes 		  = nullptr;      
	Ram_t* 		   ram 		      = nullptr;		 
	Stack_t   	   stack 		  = {};
	Argument_t     regs[REGS_NUM] = {};
	Argument_t     ip 		      = -1;

} Processor;

//{----------------------------------------------------------------------------------------------------------------------------------------


ERROR_CODES Execute(Processor* PROCESSOR);
ERROR_CODES ProcessorCtor(Processor* AMD_Ryzen, char* instructions);
void ProcessorDtor(Processor* IntelPentium);
ERROR_CODES ScanCodes(Instruction_t* codes, FILE* executableFile);


#endif // PROCESSOR_H
