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


#define STEP_VALIDATION
// #define DO_YOU_REALLY_WANNA_DO_THAT

#ifdef ON_DEBUG
#undef ON_DEBUG
#endif

#ifdef STEP_VALIDATION
	#define ON_DEBUG(expr) expr
#else
	#define ON_DEBUG(expr)
#endif


//{--------------------------------------------------------General-Info--------------------------------------------------------------------

typedef int32_t		VideoMem_t;
typedef StackElem_t	Reg_t;
typedef StackElem_t Ram_t;


const uint64_t MEM_SIZE = 16384;  /// 16 MB in bytes
const uint64_t REGS_NUM = 4;	  /// 4 registers


const int MAX_DEBUG_FIELD_LENGTH = 100;
const int MAX_RAM_DEBUG_OUTPUT   = 10;

const int NEUTRAL_NUM            = 66666;

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------DSL-----------------------------------------------------------------------

#define STACK       PROCESSOR->stack
#define IP	 	    PROCESSOR->ip
#define CODES 	    PROCESSOR->codes
#define RAM         PROCESSOR->ram
#define REGS 	    PROCESSOR->regs
#define VIDEOMEM    PROCESSOR->videomem
#define MEM_PTR	    PROCESSOR->memPtr

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
	int64_t        ip 		      = -1;
	int64_t        memPtr	      = -1;

} Processor;

//{----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Main-Execition-Func-------------------------------------------------------------

/**
 * @brief      	   Executes machine codes
 *
 * @param[in]      PROCESSOR       The processor object pointer
 * @param[in]      executableFile  The executable file pointer
 *
 * @return     	   The error's code
 */
ERROR_CODES Execute(Processor* PROCESSOR, FILE* executableFile);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Processor-Ctor-&-Dtor-----------------------------------------------------------

/**
 * @brief      		Processor constructor
 *
 * @param[in,out]   AMD_Ryzen  Not Intel
 *
 * @return     		The erro's code
 */
ERROR_CODES ProcessorCtor(Processor* AMD_Ryzen);


/**
 * @brief      		   Processor destructor
 *
 * @param[in,out]      IntelPentium  The legendary Pentium
 */
void ProcessorDtor(Processor* IntelPentium);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------File-Work-Funcs-----------------------------------------------------------------

/**
 * @brief      Checks if signature and vesrion are valid
 *
 * @param[in]  codes  The codes pointer
 *
 * @return     The error's code
 */
ERROR_CODES CheckFile(Instruction_t* codes);


/**
 * @brief      Gets the file size
 *
 * @param[in]  executableFile  The executable file pointer
 *
 * @return     The file size.
 */
size_t GetFileSize(FILE* executableFile);

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Step-Dump-Funcs-----------------------------------------------------------------

#ifdef STEP_VALIDATION

/**
 * @brief      		   Dumps stack fields
 *
 * @param[in]	       PROCESSOR  The processor
 * @param[in,out]      logFile    The log file pointer
 *
 * @return     		   The error's code
 */
ERROR_CODES DumpStack(Processor* PROCESSOR, FILE* logFile);


/**
 * @brief      		   Dumps RAM fields
 *
 * @param[in]	       PROCESSOR  The processor
 * @param[in,out]      logFile    The log file
 *
 * @return     		   The error's code
 */
ERROR_CODES DumpRAM(Processor* PROCESSOR, FILE* logFile);


/**
 * @brief      		   Dumps instruction pointer
 *
 * @param[in]          PROCESSOR  The processor
 * @param[in,out]      logFile    The log file
 *
 * @return     		   The error's code
 */
ERROR_CODES DumpIP(Processor* PROCESSOR, FILE* logFile);


/**
 * @brief      		   Dumps regs
 *
 * @param[in]   	   PROCESSOR  The processor
 * @param[in,out]      logFile    The log file
 *
 * @return     		   The error's code
 */
ERROR_CODES DumpRegs(Processor* PROCESSOR, FILE* logFile);


/**
 * @brief      		   Dumps one step info
 *
 * @param      		   PROCESSOR  The processor
 * @param[in]  		   stepCount  The step count
 * @param[in,out]      logFile    The log file
 *
 * @return     		   The error's code
 */
ERROR_CODES StepDump(Processor* PROCESSOR, int stepCount, FILE* logFile);

#endif // STEP_VALIDATION

//}----------------------------------------------------------------------------------------------------------------------------------------


#endif // PROCESSOR_H
