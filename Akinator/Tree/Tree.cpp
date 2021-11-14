/**
 * @defgroup   TREE Tree
 *
 * @brief      This file implements Tree.
 *
 * @author     Stas
 * @date       2021
 */


#include "Tree.h"


TREE_ERRORS Tree_Ctor(Tree_t* tree, TreeElem_t initialValue)
{
	Logger_assert(tree && "Inappropriate tree pointer");

	Logger_assert(initialValue && "What's wrong with you!?");

	tree->root = (Node_t*) calloc(1, sizeof (Node_t));

	if (tree->root == nullptr) {
		Logger_return(TREE_ALLOCATION_ERROR);
	}

	else {
		tree->root->value = initialValue;
		tree->root->left  = nullptr;
		tree->root->right = nullptr;
	}

	tree->size = 1;

	return TREE_NO_ERROR;
}

TREE_ERRORS Tree_Dtor(Tree_t* tree)
{
	Logger_assert(tree && "Inappropriate tree pointer");

	Logger_assert(tree->root && "I've got no root...")

	Tree_RemoveNode(tree->root);	

	tree->root = (Node_t*) TREE_POISON_POINTER;
	tree->size = (size_t)  TREE_POISON_NUMBER;

	return TREE_NO_ERROR;
}


TREE_ERRORS Tree_InsertNode(Node_t* node, TreeElem_t insertValue)
{
	Logger_assert(node && "Node must not be nullptr");

	if (insertValue > node->value) {

		if (node->right) {
			Tree_InsertNode(node->right, insertValue);
		}
			
		else {
			node->right = Tree_CreateNode(insertValue);
		}
	}

	else {

		if (node->left) {
			Tree_InsertNode(node->left, insertValue);
		}

		else {
			node->left = Tree_CreateNode(insertValue);
		}
	}

	return TREE_NO_ERROR;
}


TREE_ERRORS Tree_RemoveNode(Node_t* node)
{
	Logger_assert(node && "Inappropriate node pointer");

	if (node->left != nullptr) {
		Tree_RemoveNode(node->left);
	}

	if (node->right != nullptr) {
		Tree_RemoveNode(node->right);
	}

	node->left  = nullptr;
	node->right = nullptr;

	node->value = (TreeElem_t) TREE_POISON_NUMBER;

	free(node);

	return TREE_NO_ERROR;
}


Node_t* Tree_CreateNode(TreeElem_t nodeValue)
{
	Node_t* newNode = (Node_t*) calloc(1, sizeof (Node_t));

	if (!newNode) {
		return nullptr;
	}

	newNode->value = nodeValue;

	newNode->right = nullptr;
	newNode->left  = nullptr;

	return newNode;
}
