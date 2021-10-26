/**
* @file defcmd.h
*/


DEF_CMD (push, 10, 1, 
	{
		// int arg = 0;

		// if (CODES[IP] & IMM_CONST)
		// 	arg += CODES[++IP];

		// if (CODES[IP] & REG_ARG)
		// 	arg += REGS[CODES[++IP]];

		// if (CODES[IP] & RAM_ARG)
		// 	arg += RAM[arg];

		// ++IP;
	}	
) 


DEF_CMD (pop, 11, 1,
	{
		// PUSH(CODES[IP + 1]);
		// POP	
	}
)


DEF_CMD (add, 12, 0, 
	{
		PUSH(POP + POP);
	}
)


DEF_CMD (mul, 13, 0, 
	{
		PUSH(POP * POP);
	}
)


DEF_CMD (div, 14, 0, 
	{
		PUSH(POP / POP);
	}
)


DEF_CMD (sub, 15, 0, 
	{
		PUSH(POP - POP);
	}
)


DEF_CMD (in, 20, 0, 
	{
		StackElem_t inValue = 0;
		scanf("%lld", &inValue);

		PUSH(inValue);
	}
)


DEF_CMD (out, 21, 0, 
	{
		printf("%lld\n", TOP);
	}
)


DEF_CMD (jmp, 2, 1, {})


DEF_CMD (ja, 3, 1, {})


DEF_CMD (jb, 4, 1, {})


DEF_CMD (je, 5, 1, {})


DEF_CMD (jae, 6, 1, {})


DEF_CMD (jbe, 7, 1, {})


DEF_CMD	(hlt, 0, 0, {})


DEF_CMD (nop, 1, 0, {})


#undef DEF_CMD
