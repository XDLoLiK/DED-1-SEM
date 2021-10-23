/**
 * @file Processor.h
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdio.h>
#include <assert.h>

#include "Assembler.h"
#include "Disassembler.h"

#include "..\Stack\Stack.h"

#include "Commands.h"


const uint64_t MEM_SIZE = 524288; // 512 MB
const uint64_t REGS_NUM = 4;	  // 4 registers


#define DEF_CMD(cmd, num, args, code) 			\
												\
	case (CMD_##cmd):							\
		code;									\
		ip += 1 + (args);						\
		break;						


typedef struct processor {

	Stack_t   stack 		 = {};
	uint64_t  regs[REGS_NUM] = {};
	uint64_t* ip 		     = nullptr;
	void* 	  RAM 			 = nullptr;
	void* 	  codes 		 = nullptr;
	void* 	  videomem 		 = nullptr;

} Processor;




//          !!!!!!!!!!!!!!!!!!





StackElem_t ProcessorSub(Stack_t* stack);
StackElem_t ProcessorMul(Stack_t* stack);
StackElem_t ProcessorDiv(Stack_t* stack);
StackElem_t ProcessorAdd(Stack_t* stack);
StackElem_t ProcessorOut(Stack_t* stack, FILE* destFile);
StackElem_t ProcessorIn(Stack_t* stack, StackElem_t inValue);

ERROR_CODES ProcessorExecute(Processor* IntelCore);
ERROR_CODES ProcessorHlt(int exitCode);

ERROR_CODES ProcessorCtor(Processor* brandNewProc);
void ProcessorDtor(Processor* oldFashionedProc);


#undef DEF_CMD


#endif // PROCESSOR_H
