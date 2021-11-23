/**
 * @defgroup   MAIN main
 *
 * @brief      This file implements main.
 *
 * @author     Stas
 * @date       2021
 */


#include "Differentiator/Differentiator.h"


int main()
{
	Logger_Init();

	bool running = true;

	while (running)
	{
		char expression[MAX_EXPRESSION_LEN] = "";
		Differentiator_ScanExpression(expression);

		Tree_t* expressionTree = Differentiator_CreateTree(expression);	
		Differentiator_Differentiate (&expressionTree);
	}

	Logger_Finish();

	return 0;
}
