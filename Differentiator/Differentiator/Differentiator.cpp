/**
 * @defgroup   DIFFERENTIATOR Differentiator
 *
 * @brief      This file implements Differentiator.
 *
 * @author     Stas
 * @date       2021
 */


#include "Differentiator.h"


Node_t* Differentiator_Differentiate(Node_t* currentNode)
{
	Logger_assert(currentNode && "Pointer must not be NULL");

	switch (currentNode->type) 
	{
		case TYPE_CONST: return CONST(0);

		case TYPE_VAR:   return CONST(1);

		case TYPE_OP:    

			switch (currentNode->value)
			{
				case OP_ADD: return ADD(DL, DR);

				case OP_SUB: return SUB(DL, DR);

				case OP_MUL: return ADD(MUL(DL, R), MUL(L, DR));

				case OP_DIV: return DIV(SUB(MUL(DL, R), MUL(DR, L)), POW(R, 2));

				case OP_POW: return NULL;

				case OP_SIN: return MUL(COS(L), DL);

				case OP_COS: return MUL(SUB(0, SIN(L)), DL);

				case OP_TG:  return MUL(DIV(1, POW(COS(L), 2)), DL);

				case OP_CTG: return MUL(DIV(SUB(0, 1), POW(SIN(L), 2)), DL);

				case OP_LOG: return NULL;

				case OP_LN:  return MUL(DIV(1, L), DL);

				case OP_LG:  return NULL;

				default: Logger_message(DIF_INVALID_OPERATION);
			}

		default: Logger_message(DIF_INVALID_TOKEN_TYPE);
	}

	return nullptr;	
}


Node_t* Differentiator_NewNode(int nodeType, int nodeValue, Node_t* nodeLeft, Node_t* nodeRight)
{
	Logger_assert(nodeLeft  && "Pointer must not be NULL");
	Logger_assert(nodeRight && "Pointer must not be NULL");

	Node_t* newNode = (Node_t*) calloc(1, sizeof (Node_t));

	if (newNode == nullptr)
	{
		Logger_message(DIF_ALLOCATION_ERROR);
		return nullptr;
	}

	newNode->type  = nodeType;
	newNode->value = nodeValue;

	newNode->left  = nodeLeft;
	newNode->right = nodeRight;

	return newNode;
}


DIFFERENTIATOR_ERRORS Differentiator_ScanExpression(const char* exprBuffer)
{
	Logger_assert(buffer && "Pointer must not be NULL");

	char filePath[MAX_FILE_PATH_LEN] = "";

	printf("Enter file path: ");
	scanf(" %s", &filePath);

	FILE* toDifferentiate = fopen(filePath, "r");

	if (toDifferentiate == nullptr)
		Logger_return(DIF_UNABLE_TO_OPEN_FILE);

	int scanned = fgets(exprBuffer, MAX_EXPRESSION_LEN, toDifferentiate);

	if (scanned == 0)
		Logger_return(DIF_SCAN_ERROR);

	return DIF_NO_ERROR;
}


Tree_t* Differentiator_CreateTree(const char* expression)
{
	Logger_assert(expression && "Pointer must not be NULL");
	
	Tree_t* expressionTree = (Tree_t*) calloc(1, sizeof (Tree_t));



	return expressionTree;
}

