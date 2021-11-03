/**
* @file Commands.h 
*/ 


#ifndef COMMANDS_H
#define COMMANDS_H


#include <inttypes.h>

#include "..\Stack\Config.h"


//{--------------------------------------------------------General-Info--------------------------------------------------------------------

typedef StackElem_t   Argument_t;
typedef unsigned char Instruction_t;
typedef uint64_t      Version_t;
typedef int			  Signature_t;

const int          MAX_CODES_CAPACITY = 4096;        // Increase if you want
const Version_t    VERSION            = 2;           // Version 2.0
const Signature_t  SIGNATURE          = 0x44454421;  // is literally 'DED!'

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Bit-Masks-----------------------------------------------------------------------

const Instruction_t RAM_ARG   	  = (Instruction_t) (1 << 7); // 10000000
const Instruction_t REG_ARG	  	  = (Instruction_t) (1 << 6); // 01000000
const Instruction_t IMM_CONST 	  = (Instruction_t) (1 << 5); // 00100000
const Instruction_t COMMAND_BITS  = (Instruction_t) (1 << 5); // 00100000

//}----------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------Commands-Numbers----------------------------------------------------------------

#define DEF_CMD(cmd, num, ...)	\
	CMD_##cmd = num,


enum COMMANDS {

	#include "DEF_CMD.h"
	CMD_MAX = 300
};

//}----------------------------------------------------------------------------------------------------------------------------------------


#endif // COMMANDS_H
