/**
* @file Commands.h 
*/ 


#ifndef COMMANDS_H
#define COMMANDS_H


#include <inttypes.h>


const uint64_t RAM_ARG   = (uint64_t) 1 << 63;
const uint64_t REG_ARG	 = (uint64_t) 1 << 62;
const uint64_t IMM_CONST = (uint64_t) 1 << 61;


#define VERSION 	1.0
#define SIGNATURE	"DED!"


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


#define DEF_CMD(cmd, num, ...)	\
	CMD_##cmd = num,


enum COMMANDS {

	#include "defcmd.h"
	CMD_MAX = 300
};


#endif // COMMANDS_H
