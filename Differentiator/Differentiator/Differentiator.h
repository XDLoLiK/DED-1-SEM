/**
 * @defgroup   DIFFERENTIATOR Differentiator
 *
 * @brief      This file implements Differentiator.
 *
 * @author     Stas
 * @date       2021
 */


#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H


#include "../../general/Logger.h"
#include "../Tree/DifferentiatorTree.h"


const int MAX_FILE_PATH_LEN  = 256;
const int MAX_EXPRESSION_LEN = 512;


#define L currentNode->left
#define R currentNode->right

#define DL Differentiator_Differentiate(currentNode->left) 
#define DR Differentiator_Differentiate(currentNode->right) 

#define CONST(num) Differentiator_NewNode(TYPE_CONST, num, NULL, NULL)

#define ADD(firstExpr, secondExpr) Differentiator_NewNode(TYPE_OP, OP_ADD, firstExpr, secondExpr)
#define SUB(firstExpr, secondExpr) Differentiator_NewNode(TYPE_OP, OP_SUB, firstExpr, secondExpr)
#define MUL(firstExpr, secondExpr) Differentiator_NewNode(TYPE_OP, OP_MUL, firstExpr, secondExpr)
#define DIV(firstExpr, secondExpr) Differentiator_NewNode(TYPE_OP, OP_DIV, firstExpr, secondExpr)
#define POW(firstExpr, secondExpr) Differentiator_NewNode(TYPE_OP, OP_POW, firstExpr, secondExpr)
#define COS(firstExpr, secondExpr) Differentiator_NewNode(TYPE_OP, OP_COS, firstExpr, secondExpr)


enum DIFFERENTIATOR_ERRORS 
{
	DIF_NO_ERROR              = 0,
	DIF_INVALID_TOKEN_TYPE    = 1,
	DIF_INVALID_OPERATION     = 2,
	DIF_ALLOCATION_ERROR      = 3,
	DIF_UNABLE_TO_OPEN_FILE   = 4,
	DIF_SCAN_ERROR            = 5,
};


enum NODE_TYPES
{
	TYPE_CONST  = 1,        // (c)' = 0
	TYPE_VAR    = 2,        // (x)' = 1
	TYPE_OP     = 3,	    // +, -, /, *, ...
};


enum OPERATIONS
{
	OP_MUL    = 42,  		// *    ASCII code
	OP_ADD    = 43,  		// +    ASCII code
	OP_SUB    = 45,  		// -    ASCII code
	OP_DIV    = 47,  		// /    ASCII code
	OP_POW    = 94,  		// ^    ASCII code
	OP_SIN    = 7563630,	// sin  ASCII code
	OP_COS    = 6516595,    // cos  ASCII code
	OP_TG     = 29799,      // tg   ASCII code
	OP_CTG    = 6517863,    // ctg  ASCII code
	OP_LOG    = 7106407,    // log  ASCII code
	OP_LN     = 27758,      // ln   ASCII code
	OP_LG     = 27751,      // lg   ASCII code
};


Node_t* Differentiator_NewNode(int nodeType, int nodeValue, Node_t* nodeLeft, Node_t* nodeRight);
DIFFERENTIATOR_ERRORS Differentiator_GetExpression(const Tree_t* exprBuffer);
Node_t* Differentiator_Differentiate(Node_t* currentNode);


#endif // DIFFERENTIATOR_H
