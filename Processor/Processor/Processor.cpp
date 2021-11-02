/**
 * @file Processor.cpp
 */


#include "Processor.h"


//{--------------------------------------------------------DEF-CMD-for-processor-----------------------------------------------------------

#define DEF_CMD(cmd, num, argsType, code)			\
													\
	case (CMD_##cmd):								\
		code;										\
		IP += CMD_SIZE;								\
		break;						

//{----------------------------------------------------------------------------------------------------------------------------------------


ERROR_CODES Execute(Processor* PROCESSOR, FILE* executableFile)
{
	assert(PROCESSOR);
	assert(executableFile);

	printf(">>> Execution started ...\n");

	clock_t ExecutionStart = clock();

	CODES = (Instruction_t*) calloc(MAX_CODES_CAPACITY, 1);
	fread(CODES, GetFileSize(executableFile), sizeof (char), executableFile);

	fclose(executableFile);

	if (!IS_OK(CheckFile(CODES))) 
		return EXECUTION_ERROR;

	while (CODES[IP] != CMD_hlt) {

		switch (CODES[IP] % COMMAND_BITS) {

			#include "..\DEF_CMD.h" // ->
			// case (CMD_<cmd_name>):
			//     code ... 

			default: 
			  RETURN(INAPPROPRIATE_COMMAND);
		}
	}

	clock_t ExecutionEnd  = clock();
	double  ExecutionTime = (double) (ExecutionEnd - ExecutionStart) / CLOCKS_PER_SEC;

	printf(">>> Execution finished in %g\n", ExecutionTime);

	RETURN(NO_ERROR);
}


ERROR_CODES ProcessorCtor(Processor* PROCESSOR)
{
	assert(PROCESSOR);

	if (!IS_OK(StackCtor(&STACK, "processorStack")))
		RETURN(CONSTRUCTION_ERROR);

	RAM 	 = (StackElem_t*) calloc(MEM_SIZE, sizeof (char));
	VIDEOMEM = (VideoMem_t*)  calloc(MEM_SIZE, sizeof (char));    
	IP       = sizeof SIGNATURE + sizeof VERSION;	

	for (size_t i = 0; i < REGS_NUM; ++i) {
		REGS[i] = 0;
	}     		
	
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
	
	for (size_t i = 0; i < REGS_NUM; ++i) 
		REGS[i] = (Argument_t) POISON_NUMBER;

	// destroying stack
	
	StackDtor(&STACK);

	// poisoning processor fields

	IP 	     = (Argument_t)    	POISON_NUMBER;
	RAM 	 = (StackElem_t*)  	POISON_POINTER;
	CODES    = (Instruction_t*)	POISON_POINTER;
	VIDEOMEM = (VideoMem_t*)   	POISON_POINTER;
}


ERROR_CODES CheckFile(Instruction_t* codes)
{
	assert(codes);

	if (* (Signature_t*) (codes) != SIGNATURE) {
		RETURN(INAPPROPRIATE_SIGNATURE);
	}

	if (* (Version_t*) (codes + sizeof (SIGNATURE)) != VERSION) {
		RETURN(INAPPROPRIATE_VERSION);
	}

	RETURN(NO_ERROR);
}


size_t GetFileSize(FILE* executableFile)
{
	assert(executableFile);

	size_t fileSize = 0;

	fseek(executableFile, 0, SEEK_END);
	fileSize = ftell(executableFile);
	fseek(executableFile, 0, SEEK_SET);

	return fileSize;
}
