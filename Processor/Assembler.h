/**
 * @file Assembler.h
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "..\Onegin\TextSort.h"
#include "..\general\Errors.h"

#include "Commands.h"

#define DEF_CMD(cmd, num, ...)				\
											\
	else if (strcmp(command, #cmd) == 0)	\
		code[ip++] = CMD_##cmd;



#endif // ASSEMBLER_H
