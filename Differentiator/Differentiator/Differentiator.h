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


#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


#include "../../general/Logger.h"
#include "../Tree/DifferentiatorTree.h"


const int MAX_FILE_PATH_LEN  = 256;
const int MAX_EXPRESSION_LEN = 512;
const int MAX_NODE_VALUE_LEN = 512;
const int NUMBER_OF_PHRASES  = 15;


#define X_VAR    120    // 'x'  ASCII code
#define E_CONST  101    // 'e'  ASCII code
#define PI_CONST 105112 // 'pi' ASCII code


#define NODE currentNode


#define L NODE->left
#define R NODE->right

#define NEW_L Differentiator_CreateNewSubTree(L)
#define NEW_R Differentiator_CreateNewSubTree(R)

#define VALUE  NODE->value
#define LVALUE NODE->left->value
#define RVALUE NODE->right->value

#define        D(expression) Differentiator_Differentiate(expression) 
#define IN_POINT(expression) Differentiator_ReplaceVariable(currentDerivative, point)

#define NEW_NODE(node)								   Differentiator_NewNode(node->type, node->value, node->left, node->right)
#define NEW_CONST(num) 								   Differentiator_NewNode(TYPE_CONST, num, NULL, NULL)
#define NEW_OP(operationName, firstExpr, secondExpr)   Differentiator_NewNode(TYPE_OP, operationName, firstExpr, secondExpr)
#define NEW_VAR(variable)                              Differentiator_NewNode(TYPE_VAR, variable, NULL, NULL)
#define NEW_NAMED_CONST(namedConst)                    Differentiator_NewNode(TYPE_NAMED_CONST, namedConst, NULL, NULL)
#define NEW_FUNC(functionName, firstExpr, secondExpr)  Differentiator_NewNode(TYPE_FUNC, functionName, firstExpr, secondExpr)


#define ADD(firstExpr, secondExpr) NEW_OP(OP_ADD, firstExpr, secondExpr)
#define SUB(firstExpr, secondExpr) NEW_OP(OP_SUB, firstExpr, secondExpr)
#define MUL(firstExpr, secondExpr) NEW_OP(OP_MUL, firstExpr, secondExpr)
#define DIV(firstExpr, secondExpr) NEW_OP(OP_DIV, firstExpr, secondExpr)
#define POW(firstExpr, secondExpr) NEW_OP(OP_POW, firstExpr, secondExpr)


#define    LOG(firstExpr, secondExpr)  NEW_FUNC(OP_LOG, firstExpr, secondExpr)
#define    COS(expression)  		   NEW_FUNC(OP_COS,    expression, NULL)
#define    SIN(expression)  		   NEW_FUNC(OP_SIN,    expression, NULL)
#define    CTG(expression)  		   NEW_FUNC(OP_CTG,    expression, NULL)
#define     TG(expression)  		   NEW_FUNC(OP_TG,     expression, NULL)
#define     LN(expression)  		   NEW_FUNC(OP_LN,     expression, NULL)
#define     SH(expression)             NEW_FUNC(OP_SH,     expression, NULL)
#define     CH(expression)             NEW_FUNC(OP_CH,     expression, NULL)
#define  ARCTG(expression)             NEW_FUNC(OP_ARCTG,  expression, NULL)
#define ARCCTG(expression)             NEW_FUNC(OP_ARCCTG, expression, NULL)
#define ARCSIN(expression)             NEW_FUNC(OP_ARCSIN, expression, NULL)
#define ARCCOS(expression)             NEW_FUNC(OP_ARCCOS, expression, NULL)
#define     TH(expression)             NEW_FUNC(OP_TH,     expression, NULL)
#define    CTH(expression)             NEW_FUNC(OP_CTH,    expression, NULL)


#define IS_CONST(expr)  	 expr->type == TYPE_CONST
#define IS_VAR(expr)     	 expr->type == TYPE_VAR
#define IS_OP(expr)     	 expr->type == TYPE_OP
#define IS_FUNC(expr)    	 expr->type == TYPE_FUNC
#define IS_NAMED_CONST(expr) expr->type == TYPE_NAMED_CONST


#define REQUIRE(symbol) if (**expression != symbol) {Logger_message("Syntax error"); return NULL;} else (*expression)++

#define NEXT (*expression)++


enum DIFFERENTIATOR_ERRORS 
{
	DIF_NO_ERROR              = 0,
	DIF_INVALID_TOKEN_TYPE    = 1,
	DIF_INVALID_OPERATION     = 2,
	DIF_ALLOCATION_ERROR      = 3,
	DIF_UNABLE_TO_OPEN_FILE   = 4,
	DIF_SCAN_ERROR            = 5,
	DIF_IMPOISSIBLE_SYMBOL    = 6,
};


#define DEF_FUNC(operation, value, ...) operation = value,

enum OPERATIONS
{
	OP_MUL    = 42,  	// '*'   ASCII code
	OP_ADD    = 43,  	// '+'   ASCII code
	OP_SUB    = 45,  	// '-'   ASCII code
	OP_DIV    = 47,  	// '/'   ASCII code
	OP_POW    = 94,  	// '^'   ASCII code
	
	#include "Functions.h"

	#undef DEF_FUNC
};


/**
 * @brief      Differentiates an expression
 *
 * @param      NODE  The current node
 *
 * @return     Differentiated node pointer
 */
Node_t* Differentiator_Differentiate(Node_t* NODE);


/**
 * @brief      Differentiates operation
 *
 * @param      NODE  The current node
 *
 * @return     The derivative
 */
Node_t* Differentiator_DifferentiateOperation(Node_t* NODE);


/**
 * @brief      Differentiates functions
 *
 * @param      NODE  The current node
 *
 * @return     The derivative
 */
Node_t* Differentiator_DifferentiateFunction(Node_t* NODE);


/**
 * @brief      Creates new node
 *
 * @param[in]  nodeType   The node type
 * @param[in]  nodeValue  The node value
 * @param      nodeLeft   The node left
 * @param      nodeRight  The node right
 *
 * @return     Created node pointer
 */
Node_t* Differentiator_NewNode(NodeType_t nodeType, NodeValue_t nodeValue, Node_t* nodeLeft, Node_t* nodeRight);


/**
 * @brief      Creates a tree from an expression
 *
 * @param      expression  The expression tree
 *
 * @return     The differentiator errors
 */
Tree_t* Differentiator_CreateTree(char* expression);


/**
 * @brief      Copies sub tree
 *
 * @param      node  The node
 *
 * @return     start node pointer
 */
Node_t* Differentiator_CreateNewSubTree(Node_t* node);


/**
 * @brief      Main grammar rule
 *
 * @param[in]  expression  The expression
 *
 * @return     New root node pointer
 */
Node_t* Differentiator_GetGrammar(const char* expression);


/**
 * @brief      Expression rule
 *
 * @param      expression  The expression
 *
 * @return     New expression node pointer
 */
Node_t* Differentiator_GetExpression(const char** expression);


/**
 * @brief      Multiplication rule
 *
 * @param      expression  The expression
 *
 * @return     New multiplication node pointer
 */
Node_t* Differentiator_GetMultiplication(const char** expression);


/**
 * @brief      Power rule
 *
 * @param      expression  The expression
 *
 * @return     New power node pointer
 */
Node_t* Differentiator_GetPower(const char** expression);


/**
 * @brief      Brackets rule
 *
 * @param      expression  The expression
 *
 * @return     New brackets node pointer
 */
Node_t* Differentiator_GetBrackets(const char** expression);


/**
 * @brief      Functions rule
 *
 * @param      expression      The expression
 * @param[in]  functionName    The function name
 * @param[in]  operationValue  The operation value
 *
 * @return     New function pointer
 */
Node_t* Differentiator_GetFunction(const char** expression, const char* functionName, NodeValue_t functionValue);


/**
 * @brief      Number rule
 *
 * @param      expression  The expression
 *
 * @return     New number node pointer
 */
Node_t* Differentiator_GetNumber(const char** expression);


/**
 * @brief      Variable rule
 *
 * @param      expression  The expression
 *
 * @return     New variable rule
 */
Node_t* Differentiator_GetVariable(const char** expression);


/**
 * @brief      Unary sign rule
 *
 * @param      expression  The expression
 *
 * @return     Expression sign
 */
int Differentiator_GetUnarySign(const char** expression);



/**
 * @brief      Creates node depending on the coefficient
 *
 * @param      node         The node
 * @param[in]  coefficient  The coefficient
 *
 * @return     New node pointer
 */
Node_t* Differentiator_CreateNodeWithCoefficient(Node_t* node, int coefficient);


/**
 * @brief      Skips all the white spaces
 *
 * @param      expression  The expression
 *
 * @return     number of white spaces skipped
 */
int Differentiator_SkipWhiteSpaces(char** expression);


/**
 * @brief      Higher order derivative
 *
 * @param      startNode  The start node
 * @param[in]  order      The order
 *
 * @return     Derivative
 */
Node_t* Differentiator_HigherOrderDerivative(Node_t* startNode, int order);


/**
 * @brief      ...
 *
 * @param      NODE   The node
 * @param[in]  point  The point
 *
 * @return     ...
 */
Node_t* Differentiator_ReplaceVariable(Node_t* NODE, int point);


/**
 * @brief      Shows result
 *
 * @param      NODE  The current node
 *
 * @return     0
 */
DIFFERENTIATOR_ERRORS Differentiator_ShowResult(FILE* destFile, Node_t* NODE);


/**
 * @brief      Print a single node
 *
 * @param      NODE  The current node
 *
 * @return     Node pointer
 */
Node_t* Differentiator_PrintNode(Node_t* NODE);


/**
 * @brief      Tree simplification
 *
 * @param      startNode  The start node
 *
 * @return     Simplified tree
 */
Node_t* Differentiator_Simplify(Node_t* startNode);


/**
 * @brief      Multiplication by one simplification
 *
 * @param      NODE  The node
 *
 * @return     Whether simplification has been made or not
 */
bool Differentiator_MultiplicationByOne(Node_t* NODE);


/**
 * @brief      Zero multiplication simplification
 *
 * @param      NODE  The current node
 *
 * @return     Whether simplification has been made or not
 */
bool Differentiator_ZeroMultiplication(Node_t* NODE);


/**
 * @brief      Empty nodes simplification
 *
 * @param      NODE  The current node
 *
 * @return     Whether simplification has been made or not
 */
bool Differentiator_EmptyNodes(Node_t* NODE);


/**
 * @brief      Consecutive operations simplification
 *
 * @param      NODE  The current node
 *
 * @return     Whether simplification has been made or not
 */
bool Differentiator_ConsecutiveOperations(Node_t* NODE);


/**
 * @brief      Gets the operation's order
 *
 * @param      node  The node
 *
 * @return     Operation order
 */
int Differentiator_GetOrder(Node_t* node);


/**
 * @brief      Taylor series
 *
 * @param      function  The function
 * @param[in]  order     The order
 * @param[in]  point     The point
 *
 * @return     Taylor expansion tree
 */
Node_t* Differentiator_TaylorExpansion(Node_t* function, int order, int point);


/**
 * @brief      Prints random phrases
 *
 * @return     random phrase index
 */
int Differentiator_PrintRandomPhrase();


/**
 * @brief      ...
 *
 * @param      destFile  The destination file
 * @param      NODE      The node
 */
void Differentiator_DumpToTex(FILE* destFile, Node_t* NODE);


#endif // DIFFERENTIATOR_H
