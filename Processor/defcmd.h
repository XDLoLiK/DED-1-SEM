/**
* @file defcmd.h
*/


#ifndef DEFCMD_H
#define DEFCMD_H


DEF_CMD (push, 22, 1, 
	{
		StackPush(&IntelCore->stack, IntelCore->codes[ip + 1]);
	}
) 


DEF_CMD (pop, 33, 1,
	{
		StackPush (&IntelCore->stack, IntelCore->codes[ip + 1]);
		StackPop  (&IntelCore->stack);	
	}
)


DEF_CMD (add, 11, 0, 
	{
		StackPush(&IntelCore->stack, StackPop(IntelCore->stack) + StackPop(IntelCore->stack));
	}
)


DEF_CMD (mul, 12, 0, 
	{
		StackPush(&IntelCore->stack, StackPop(IntelCore->stack) * StackPop(IntelCore->stack));
	}
)


DEF_CMD (div, 13, 0, 
	{
		StackPush(&IntelCore->stack, StackPop(IntelCore->stack) / StackPop(IntelCore->stack));
	}
)


DEF_CMD (sub, 14, 0, 
	{
		StackPush(&IntelCore->stack, StackPop(IntelCore->stack) - StackPop(IntelCore->stack));
	}
)


DEF_CMD (in, 15, 0, 
	{
		StackElem_t inValue = 0;
		scanf("%lg", &inValue);

		StackPush(&IntelCore->stack, inValue);
	}
)


DEF_CMD (out, 16, 0, 
	{
		printf("%lg\n", StackTop(&IntelCore->stack));
	}
)


#endif // DEFCMD_H
