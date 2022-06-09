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

	int ord = 1;

	printf("Order: ");

	scanf(" %d ", &ord);

	char expr[100] = "";

	gets(expr);

	printf("\n\n");


	Tree_t* expressionTree = Differentiator_CreateTree(expr);

	expressionTree->root   = Differentiator_HigherOrderDerivative(expressionTree->root, ord);

	// expressionTree->root = Differentiator_TaylorExpansion(expressionTree->root, ord, 0);

	expressionTree->root = Differentiator_Simplify(expressionTree->root);

	DifferentiatorTree_DumpTree(expressionTree->root);

	printf("Finally, we get:\n");

	Differentiator_ShowResult(stdout, expressionTree->root);

	printf("\n\n");

	FILE* dumpFile = fopen("derivative.txt", "w");

	Differentiator_DumpToTex(dumpFile, expressionTree->root);

	Logger_Finish();

	return 0;
}
	