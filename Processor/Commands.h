/**
* @file Commands.h 
*/ 


#ifndef COMMANDS_H
#define COMMANDS_H


#include <inttypes.h>

#include "../Stack/Config.h"


typedef StackElem_t   Argument_t;
typedef unsigned char Instruction_t;


const Instruction_t RAM_ARG   	  = (Instruction_t) 1 << 7;
const Instruction_t REG_ARG	  	  = (Instruction_t) 1 << 6;
const Instruction_t IMM_CONST 	  = (Instruction_t) 1 << 5;
const Instruction_t COMMAND_BITS  = (Instruction_t) 1 << 5;


#define VERSION 	1.0
#define SIGNATURE	"DED!"


#define DEF_CMD(cmd, num, ...)	\
	CMD_##cmd = num,


enum COMMANDS {

	#include "DEF_CMD.h"
	CMD_MAX = 300
};


#endif // COMMANDS_H
