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


typedef struct node_t
{
	int type  = 0;
	int value = 0; 

	node_t* left  = nullptr;
	node_t* right = nullptr;

} Node_t;


typedef struct tree_t
{
	node_t* root = nullptr;

} Tree_t;


#endif // DIFFERENTIATOR_TREE_H
