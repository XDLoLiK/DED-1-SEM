/**
* @file DEF_CMD.h
*/


/*

~ LANGUAGE DESCRIPTION ~

...

*/


/*
 * @brief Simply pushes a certain value into stack
 */
DEF_CMD (push, 10, 2, 
	{
		INSTR_T INSTRUCTION = CODES[IP];
		ARG_T   ARG         = 0;

		IP += CMD_SIZE;

		if (INSTRUCTION & REG_ARG) {
			ARG += REGS[(ARG_T) CODES[IP]];
			IP  += ARG_SIZE; 
		}

		if (INSTRUCTION & IMM_CONST) {
			ARG += (ARG_T) CODES[IP];
			IP  += ARG_SIZE; 
		}

		if (INSTRUCTION & RAM_ARG) {
			ARG = RAM[ARG];
		}

		IP -= CMD_SIZE;
		
		PUSH(ARG);
	}
) 


/*
 * @brief Pops the top stack value from stack and puts it
 * 	      somwhere else (register, RAM)
 */
DEF_CMD (pop, 11, 2,
	{
		INSTR_T INSTRUCTION = CODES[IP];
		ARG_T   ARG 		= POP;

		IP += CMD_SIZE;

		if (INSTRUCTION & RAM_ARG) {

			ARG_T INDEX = 0;

			if (INSTRUCTION & REG_ARG) {

				INDEX += REGS[(ARG_T) CODES[IP]];
				IP    += ARG_SIZE;
			}	
			
			if (INSTRUCTION & IMM_CONST) {
				
				INDEX += (ARG_T) CODES[IP];
				IP    += ARG_SIZE;
			}

			RAM[INDEX] = ARG;
		}

		else {

			if (INSTRUCTION & REG_ARG) {

				REGS[(ARG_T) CODES[IP]] = ARG;
				IP += ARG_SIZE;
			}	

			if (INSTRUCTION & IMM_CONST) {

				IP += ARG_SIZE;
			}
		}

		IP -= CMD_SIZE;
	}
)


/*
 * @brief adds the first top stack element to the second
 * 		  top stack element and pops them both (pushes the result instead)
 */
DEF_CMD (add, 12, 0, 
	{
		PUSH(POP + POP);
	}
)


/*
 * @brief multiplies the first top stack element by the second
 * 		  top stack element and pops them both (pushes the result instead)
 */
DEF_CMD (mul, 13, 0, 
	{
		PUSH(POP * POP);
	}
)


/*
 * @brief divides the first top stack element by the second
 * 		  top stack element and pops them both (pushes the result instead)
 */
DEF_CMD (div, 14, 0, 
	{
		PUSH(POP / POP);
	}
)


/*
 * @brief substracts the second top stack element from the first
 * 		  top stakc element and pops them both (pushes the result instead)
 */
DEF_CMD (sub, 15, 0, 
	{
		PUSH(POP - POP);
	}
)


/*
 * @brief scans a value from the user and pushes it to stack
 */
DEF_CMD (in, 20, 0, 
	{
		ARG_T IN_ARG = 0;
		scanf("%ld", (long*) &IN_ARG);

		PUSH(IN_ARG);
	}
)


/*
 * @brief prints out the top stack element to the console
 */
DEF_CMD (out, 21, 0, 
	{
		printf("%ld\n", (long) TOP);
	}
)


/*
 * @brief jumps to a lable
 */
DEF_CMD (jmp, 2, 1, 
	{
		IP = (ARG_T) CODES[IP + CMD_SIZE] - CMD_SIZE;
	}
)


/*
 * @brief jumps to a lable if top stack element is above
 * 		  the element right after it (abd pops them both)
 */
DEF_CMD (ja, 3, 1, 
	{
		if (POP > POP)
			IP = (ARG_T) CODES[IP + CMD_SIZE] - CMD_SIZE;

		else
			IP += ARG_SIZE;
	}
)


/*
 * @brief jumps to a lable if top stack element is bellow
 * 		  the element right after it (abd pops them both)
 */
DEF_CMD (jb, 4, 1, 
	{
		if (POP < POP)
			IP = (ARG_T) CODES[IP + CMD_SIZE] - CMD_SIZE;

		else
			IP += ARG_SIZE;
	}
)


/*
 * @brief jumps to a lable if top stack element equals
 * 		  the element right after it (abd pops them both)
 */
DEF_CMD (je, 5, 1, 
	{
		if (POP == POP)
			IP = (ARG_T) CODES[IP + CMD_SIZE] - CMD_SIZE;

		else
			IP += ARG_SIZE;
	}
)


/*
 * @brief jumps to a lable if top stack element is above or equals
 * 		  the element right after it (abd pops them both)
 */
DEF_CMD (jae, 6, 1, 
	{
		if (POP >= POP)
			IP = (ARG_T) CODES[IP + CMD_SIZE] - CMD_SIZE;

		else
			IP += ARG_SIZE;
	}
)


/*
 * @brief jumps to a lable if top stack element is bellow or equals
 * 		  the element right after it (abd pops them both)
 */
DEF_CMD (jbe, 7, 1, 
	{
		if (POP <= POP)
			IP = (ARG_T) CODES[IP + CMD_SIZE] - CMD_SIZE;

		else
			IP += ARG_SIZE;
	}
)


/*
 * @brief jumps to the address which is the top stack element
 */
DEF_CMD (ret, 8, 0, 
	{
		IP = POP;
	}
)


/*
 * @brief jumps to a lable and pushes return address into stack
 */
DEF_CMD (call, 9, 1, 
	{
		PUSH(IP);
		IP = (ARG_T) CODES[IP + CMD_SIZE] - CMD_SIZE;
	}
)


/*
 * @brief marks the end of the program
 */
DEF_CMD	(hlt, 0, 0, {})


/*
 * @brief literally no operation
 */
DEF_CMD (nop, 1, 0, {})


#undef DEF_CMD
