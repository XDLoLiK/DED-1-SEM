/**
 * @file Processor.h
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H


#include <stdio.h>
#include <io.h>
#include <assert.h>
#include <time.h>

#include "..\Commands.h"
#include "..\..\Stack\Stack.h"
#include "..\..\general\Errors.h"


//{--------------------------------------------------------General-Info--------------------------------------------------------------------

typedef int32_t		VideoMem_t;
typedef StackElem_t	Reg_t;
typedef StackElem_t Ram_t;


const uint64_t MEM_SIZE = 16384;  /// 16 MB in bytes
const uint64_t REGS_NUM = 4;	  /// 4 registers

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------DSL-----------------------------------------------------------------------

#define STACK       PROCESSOR->stack
#define IP	 	    PROCESSOR->ip
#define CODES 	    PROCESSOR->codes
#define RAM         PROCESSOR->ram
#define REGS 	    PROCESSOR->regs
#define VIDEOMEM    PROCESSOR->videomem

#define PUSH(arg)   StackPush(&STACK, (arg))
#define POP   	    StackPop (&STACK)
#define TOP         StackTop (&STACK)

#define ARG_SIZE    sizeof (Argument_t)
#define CMD_SIZE    sizeof (Instruction_t)

#define ax		    REGS[0]
#define bx		    REGS[1]
#define cx	   	    REGS[2]
#define dx  	    REGS[3]

#define ARG_T       Argument_t
#define INSTR_T     Instruction_t

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


/**
 * @brief      Executes machine codes
 *
 * @param      PROCESSOR       The processor object pointer
 * @param      executableFile  The executable file pointer
 *
 * @return     The error's code
 */
ERROR_CODES Execute(Processor* PROCESSOR, FILE* executableFile);


/**
 * @brief      Processor constructor
 *
 * @param      AMD_Ryzen  Not Intel
 *
 * @return     The erro's code
 */
ERROR_CODES ProcessorCtor(Processor* AMD_Ryzen);


/**
 * @brief      Processor destructor
 *
 * @param      IntelPentium  The legendary Pentium
 */
void ProcessorDtor(Processor* IntelPentium);


/**
 * @brief      Checks if signature and vesrion are valid
 *
 * @param      codes  The codes pointer
 *
 * @return     The error's code
 */
ERROR_CODES CheckFile(Instruction_t* codes);


/**
 * @brief      Gets the file size
 *
 * @param      executableFile  The executable file pointer
 *
 * @return     The file size.
 */
size_t GetFileSize(FILE* executableFile);


#endif // PROCESSOR_H