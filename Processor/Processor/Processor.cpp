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

	ON_DEBUG(int stepCount = 1);

	while (CODES[IP] != CMD_hlt) {

		switch (CODES[IP] % COMMAND_BITS) {

			#include "..\DEF_CMD.h" // ->
			// case (CMD_<cmd_name>):
			//     code ... 

			default: 
				RETURN(INAPPROPRIATE_COMMAND);
		}

		ON_DEBUG(

			getchar();
			StepDump(PROCESSOR, stepCount, stdout);
			++stepCount;
		
		) // ON_DEBUG	
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
		REGS[i] = (Argument_t) NEUTRAL_NUM;

	// destroying stack
	
	StackDtor(&STACK);

	// poisoning processor fields

	IP 	     = (Argument_t)    	NEUTRAL_NUM;
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


#ifdef STEP_VALIDATION

ERROR_CODES StepDump(Processor* PROCESSOR, int stepCount, FILE* logFile)
{
	assert(PROCESSOR);
	assert(logFile);

	for (int i = 0; i < MAX_DEBUG_FIELD_LENGTH / 2; ++i)
		fprintf(logFile, "=");

	fprintf(logFile, "STEP=%d", stepCount);

	for (int i = 0; i < MAX_DEBUG_FIELD_LENGTH / 2; ++i)
		fprintf(logFile, "=");
	fprintf(stdout, "\n\n");

	// Various dumps

	if (!IS_OK(DumpRegs(PROCESSOR, logFile)))
		RETURN(EXECUTION_ERROR);

	if (!IS_OK(DumpIP(PROCESSOR, logFile)))
		RETURN(EXECUTION_ERROR);

	if (!IS_OK(DumpStack(PROCESSOR, logFile)))
		RETURN(EXECUTION_ERROR);

#ifdef DO_YOU_REALLY_WANNA_DO_THAT

	if (!IS_OK(DumpRAM(PROCESSOR, logFile)))
		RETURN(EXECUTION_ERROR);

#endif // DO_YOU_REALLY_WANNA_DO_THAT

	RETURN(NO_ERROR);
}


ERROR_CODES DumpRegs(Processor* PROCESSOR, FILE* logFile)
{
	assert(PROCESSOR);
	assert(logFile);

	fprintf(logFile, "REGS\n\n");

	for (int i = 0; i < (int) REGS_NUM; ++i)
		fprintf(logFile, "+------------+   ");

	fprintf(logFile, "\n");

	for (int curReg = 0; curReg < (int) REGS_NUM; ++curReg)
		fprintf(logFile, "|     %cx     |   ", 'a' + (char) curReg);

	fprintf(logFile, "\n");

	for (int i = 0; i < (int) REGS_NUM; ++i)
		fprintf(logFile, "+------------+   ");

	fprintf(logFile, "\n\n");	

	for (int i = 0; i < (int) REGS_NUM; ++i)
		fprintf(logFile, "+------------+   ");

	fprintf(logFile, "\n");

	for (int i = 0; i < (int) REGS_NUM; ++i)
		fprintf(logFile, "| %10ld |   ", (long) REGS[i]);

	fprintf(logFile, "\n");	

	for (int i = 0; i < (int) REGS_NUM; ++i)
		fprintf(logFile, "+------------+   ");

	fprintf(logFile, "\n\n");	

	RETURN(NO_ERROR);
}


ERROR_CODES DumpIP(Processor* PROCESSOR, FILE* logFile)
{
	assert(PROCESSOR);
	assert(logFile);

	fprintf(logFile, "IP\n\n");

	fprintf(logFile, "+----+   +------------+\n");
	fprintf(logFile, "| ip |   | %10ld |\n", (long) IP);
	fprintf(logFile, "+----+   +------------+\n\n");

	RETURN(NO_ERROR);
}


ERROR_CODES DumpRAM(Processor* PROCESSOR, FILE* logFile)
{
	assert(PROCESSOR);
	assert(logFile);

	fprintf(logFile, "RAM\n\n");

	int RAMsOut = 0;

	for (int i = 0; i < (int) MEM_SIZE; ++i) {
		
		if (RAM[i] != (Ram_t) NEUTRAL_NUM) {
		
			fprintf(logFile, "+---------------+   +------------+\n");
			fprintf(logFile, "| RAM [%-7d] |   | %10ld |\n", i, (long) RAM[i]);
			fprintf(logFile, "+---------------+   +------------+\n\n");

			++RAMsOut;
		}

		if (RAMsOut >= MAX_RAM_DEBUG_OUTPUT) {
			break;
		}
	}

	RETURN(NO_ERROR);
}


ERROR_CODES DumpStack(Processor* PROCESSOR, FILE* logFile)
{
	assert(PROCESSOR);
	assert(logFile);

	fprintf(logFile, "STACK\n\n");

	if (STACK.size == 0) {
		
		fprintf(logFile, "[EMPTY]\n\n");
	}

	for (int i = 0; i < (int) STACK.size; ++i) {
		
		if (STACK.data[i] != (StackElem_t) NEUTRAL_NUM) {
		
			fprintf(logFile, "+-----------------+   +------------+\n");
			fprintf(logFile, "| STACK [%-7d] |   | %10ld |\n", i, (long) STACK.data[i]);
			fprintf(logFile, "+-----------------+   +------------+\n\n");
		}
	}

	RETURN(NO_ERROR);
}

#endif // STEP_VALIDATION
