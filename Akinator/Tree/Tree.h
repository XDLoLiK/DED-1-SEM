/**
 * @defgroup   TREE Tree
 *
 * @brief      This file implements Tree.
 *
 * @author     Stas
 * @date       2021
 */


#ifndef TREE_H
#define TREE_H


#include <stdio.h>
#include <assert.h>

#include "../../general/Logger.h"

#include "TreeConfig.h"


typedef struct node_t {

	TreeElem_t value = NULL;
	node_t*    left  = nullptr;
	node_t*    right = nullptr;

} Node_t;


typedef struct tree_t {
	
	node_t* root = nullptr;
	size_t  size = 0;

} Tree_t;


enum TREE_ERRORS {

	TREE_NO_ERROR 	      = 0,
	TREE_ALLOCATION_ERROR = 1,
};


enum TREE_POISON_VALUES {

	TREE_POISON_NUMBER   = 65000,
	TREE_POISON_POINTER  = 666,
};


/**
 * @brief      Tree constructor
 *
 * @param      tree          The tree
 * @param[in]  initialValue  The initial value
 *
 * @return     The tree errors
 */
TREE_ERRORS Tree_Ctor(Tree_t* tree, TreeElem_t initialValue);


/**
 * @brief      Tree destructor
 *
 * @param      tree  The tree
 *
 * @return     The tree errors
 */
TREE_ERRORS Tree_Dtor(Tree_t* tree);


/**
 * @brief      Inserts a value after a given node
 *
 * @param      node         The node
 * @param[in]  insertValue  The insert value
 *
 * @return     The tree errors
 */
TREE_ERRORS Tree_InsertNode(Node_t* node, TreeElem_t insertValue);


/**
 * @brief      Removes a node from a tree
 *
 * @param      node  The node
 *
 * @return     The tree errors
 */
TREE_ERRORS Tree_RemoveNode(Node_t* node);


/**
 * @brief      Creates new node
 *
 * @param[in]  nodeValue  The node value
 *
 * @return     New node pointer
 */
Node_t* Tree_CreateNode(TreeElem_t nodeValue);


#endif // TREE_H
