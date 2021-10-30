/**
 * @file Processor.cpp
 */


#include "Processor.h"


//{--------------------------------------------------------DEF-CMD-for-processor-----------------------------------------------------------

#define DEF_CMD(cmd, num, args, code)				\
													\
	case (CMD_##cmd):								\
		code;										\
		IP += 1;									\
		break;						

//{----------------------------------------------------------------------------------------------------------------------------------------


ERROR_CODES Execute(Processor* PROCESSOR)
{
	while (CODES[IP] != CMD_hlt) {

		switch (CODES[IP] % COMMAND_BITS) {
		
			#include "DEF_CMD.h" // ->
			// case (CMD_<cmd_name>):
			//     code ... 

			default:
			  RETURN(INAPPROPRIATE_COMMAND);
		}
	}

	RETURN(NO_ERROR);
}


ERROR_CODES ProcessorCtor(Processor* PROCESSOR, FILE* executableFile)
{
	assert(PROCESSOR);

	if (!IS_OK(StackCtor(&STACK, "processorStack")))
		RETURN(CONSTRUCTION_ERROR);

	RAM 	 = (StackElem_t*) calloc(MEM_SIZE, 1);                
	VIDEOMEM = (VideoMem_t*)  RAM + MEM_SIZE / 2;      
	IP       = 0;	     		

	// if (!IS_OK(ScanCodes())) {
		// 
	// }
	
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

	IP 	     = (int64_t)  	   	POISON_NUMBER;
	RAM 	 = (StackElem_t*)  	POISON_POINTER;
	CODES    = (Instruction_t*)	POISON_POINTER;
	VIDEOMEM = (VideoMem_t*)   	POISON_POINTER;
}


ERROR_CODES ScanCodes(Instruction_t* codes, FILE* executableFile)
{
	assert(executableFile);
	assert(codes);



	RETURN(NO_ERROR);
}
