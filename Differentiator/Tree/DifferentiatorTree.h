/**
 * @defgroup   DIFFERENTIATORTREE Differentiator Tree
 *
 * @brief      This file implements Differentiator Tree.
 *
 * @author     Stas
 * @date       2021
 */


#ifndef DIFFERENTIATOR_TREE_H
#define DIFFERENTIATOR_TREE_H


#include "../../general/Logger.h"


typedef unsigned long long NodeType_t;

typedef unsigned long long NodeValue_t;


typedef struct node_t
{
	NodeType_t  type  = 0;
	NodeValue_t value = 0; 

	node_t* left  = nullptr;
	node_t* right = nullptr;

} Node_t;


typedef struct tree_t
{
	node_t* root = nullptr;

} Tree_t;


enum DIF_TREE_ERRORS
{
	DIF_TREE_NO_ERROR   = 0,
	DIF_TREE_DUMP_ERROR = 1,
};


enum NODE_TYPES
{
	TYPE_CONST  	  =  1,     // (c)' = 0
	TYPE_VAR    	  =  2,     // (x)' = 1
	TYPE_OP     	  =  3,     // +, -, /, *, ...
	TYPE_NAMED_CONST  =  4,     // e, pi
	TYPE_FUNC         =  5,     // cos, sin, ...
	NO_TYPE     	  = -1,
};


/**
 * @brief      Destroys the Differentiator tree object
 *
 * @param      expressionTree  The expression tree
 *
 * @return     The dif tree errors
 */
DIF_TREE_ERRORS DifferentiatorTree_TreeDtor(Tree_t* expressionTree);


/**
 * @brief      Destroys the node and its sub nodes
 *
 * @param      currentNode  The current node
 *
 * @return     The dif tree errors
 */
DIF_TREE_ERRORS DifferentiatorTree_NodeDtor(Node_t* currentNode);


/**
 * @brief      Dumps the tree
 *
 * @param      startNode  The start node
 *
 * @return     The dif tree errors
 */
DIF_TREE_ERRORS DifferentiatorTree_DumpTree(Node_t* startNode);


/**
 * @brief      Dumps sub tree
 *
 * @param      currentNode  The current node
 * @param      dotFile      The dot file
 *
 * @return     The dif tree errors
 */
DIF_TREE_ERRORS DifferentiatorTree_DumpSubTree(Node_t* currentNode, FILE* dotFile);


/**
 * @brief      Dumps a single node
 *
 * @param      currentNode  The current node
 * @param      dotFile      The dot file
 *
 * @return     The dif tree errors
 */
DIF_TREE_ERRORS DifferentiatorTree_DumpNode(Node_t* currentNode, FILE* dotFile);


#endif // DIFFERENTIATOR_TREE_H
