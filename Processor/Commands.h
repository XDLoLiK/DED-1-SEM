/**
* @file Commands.h 
*/ 


#ifndef COMMANDS_H
#define COMMANDS_H 


#define DEF_CMD(cmd, num, ...)			\
	CMD_##cmd = (num),


enum Commands {

	#include "defcmd.h"
	CMD_MAX = 0
}


#undef DEF_CMD


#endif // COMMANDS_H
