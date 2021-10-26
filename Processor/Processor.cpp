/**
 * @file Processor.cpp
 */

#include "Processor.h"


//{--------------------------------------------------------DEF-CMD-for-processor-----------------------------------------------------------

#define DEF_CMD(cmd, num, args, code) 			\
												\
	case (CMD_##cmd):							\
		code;									\
		// ip += 1 + (args);						\
		break;						

//{----------------------------------------------------------------------------------------------------------------------------------------


ERROR_CODES Execute(Processor* PROCESSOR)
{
	while (CODES[IP] != CMD_hlt) {

		switch (CODES[IP]) {
		
			#include "defcmd.h" // ->
			/* case (CMD_<cmd name> ...):
			       code ... */

			default:
			  RETURN(INAPPROPRIATE_COMMAND);
		}
	}

	RETURN(NO_ERROR);
}


ERROR_CODES ProcessorCtor(Processor* PROCESSOR)
{
	assert(PROCESSOR);

	if (StackCtor(&STACK, "processorStack") != NO_ERROR)
		RETURN(CONSTRUCTION_ERROR);

	RAM 	    = (StackElem_t*) calloc(MEM_SIZE, 1);                
	VIDEOMEM    = (VideoMem_t*)  RAM + MEM_SIZE / 2;      
	IP 		    = 0;	     				 
	
	RETURN(NO_ERROR);
}


void ProcessorDtor(Processor* PROCESSOR)
{
	assert(PROCESSOR);

	// setting allocated memory free
	
	free(RAM);
	free(CODES);
	free(VIDEOMEM);

	// poisoning registers
	
	for (int i = 0; i < REGS_NUM; ++i) 
		REGS[i] = (uint64_t) POISON_NUMBER;

	// destroying stack
	
	StackDtor(&STACK);

	// poisoning processor fields

	IP 	     = (int64_t)  	   POISON_NUMBER;
	RAM 	 = (StackElem_t*)  POISON_POINTER;
	CODES    = (Codes_t*) 	   POISON_POINTER;
	VIDEOMEM = (VideoMem_t*)   POISON_POINTER;
}


ERROR_CODES ScanCodes(FILE* executableFile, Codes_t* codes)
{
	assert(executableFile);
	assert(codes);

	RETURN(NO_ERROR);
}
