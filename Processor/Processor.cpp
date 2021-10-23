/**
 * @file Processor.cpp
 */

#include "Processor.h"


ERROR_CODES ProcessorCtor(Processor* brandNewProc)
{
	assert(brandNewProc);

	StackCtor(&brandNewProc->stack, "procStack");

	brandNewProc->RAM = calloc(MEM_SIZE, sizeof (char));
	brandNewProc->videomem = brandNewProc->RAM + MEM_SIZE / 2 * sizeof (char);

	brandNewProc->ip = &brandNewProc->regs[REGS_NUM - 1];

	brandNewProc->codes = ProcessorGetCodes(); ???????
	
	RETURN(NO_ERROR);
}


void ProcessorDtor(Processor* oldFashionedProc)
{
	assert(oldFashionedProc);

	free(oldFashionedProc->RAM);
	free(oldFashionedProc->codes);
	free(oldFashionedProc->videomem);

	for (int i = 0; i < REGS_NUM; ++i) {
		oldFashionedProc->regs[i] = (uint64_t) POISON_NUMBER;
	}

	StackDtor(&oldFashionedProc->stack);
	
	oldFashionedProc->ip 	   = (void*) POISON_POINTER;
	oldFashionedProc->RAM 	   = (void*) POISON_POINTER;
	oldFashionedProc->codes    = (void*) POISON_POINTER;
	oldFashionedProc->videomem = (void*) POISON_POINTER;
}


StackElem_t ProcessorAdd(Stack_t* stack)
{
	assert(stack);

	return StackPush(stack, StackPop(stack) + StackPop(stack));
}


StackElem_t ProcessorSub(Stack_t* stack)
{
	assert(stack);

	return StackPush(stack, StackPop(stack) - StackPop(stack));
}


StackElem_t ProcessorMul(Stack_t* stack)
{
	assert(stack);

	return StackPush(stack, StackPop(stack) * StackPop(stack));
}


StackElem_t ProcessorDiv(Stack_t* stack)
{
	assert(stack);

	return StackPush(stack, StackPop(stack) / StackPop(stack));
}


StackElem_t ProcessorOut(Stack_t* stack, FILE* destFile = stdout)
{
	assert(stack && destFile);

	fprintf(destFile, "%llu\n", StackTop(stack));

	return StackTop(stack);
}


StackElem_t ProcessorIn(Stack_t* stack, StackElem_t inValue)
{
	assert(stack);

	return StackPush(stack, inValue);
}


ERROR_CODES ProcessorExecute(Processor* IntelCore)
{
	while (true) {

		#include "defcmd.h"
		default:  RETURN(INAPPROPRIATE_COMMAND);
	}

	RETURN(NO_ERROR);
}
