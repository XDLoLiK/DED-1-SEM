/**
 * @defgroup   DIFFERENTIATORTREE Differentiator Tree
 *
 * @brief      This file implements Differentiator Tree.
 *
 * @author     Stas
 * @date       2021
 */


#include "DifferentiatorTree.h"


DIF_TREE_ERRORS DifferentiatorTree_TreeDtor(Tree_t* expressionTree)
{
	Logger_assert(expressionTree && "Pointer must not be NULL");

	DifferentiatorTree_NodeDtor(expressionTree->root);

	expressionTree->root = nullptr;

	free(expressionTree->root);
	free(expressionTree);

	return DIF_TREE_NO_ERROR;
}


DIF_TREE_ERRORS DifferentiatorTree_NodeDtor(Node_t* currentNode)
{
	Logger_assert(currentNode && "Pointer must not be NULL");

	if (currentNode->left)  DifferentiatorTree_NodeDtor(currentNode->left);
	if (currentNode->right) DifferentiatorTree_NodeDtor(currentNode->right);

	currentNode->left  = nullptr;
	currentNode->right = nullptr;

	currentNode->type  = NO_TYPE;
	currentNode->value = 0;

	free(currentNode);

	return DIF_TREE_NO_ERROR;
}


DIF_TREE_ERRORS DifferentiatorTree_DumpTree(Node_t* startNode)
{
	Logger_assert(startNode && "Start node pointer is NULL in DifferentiatorTree_DumpTree()");

	FILE* dotFile = fopen("Dumps\\Tree.dot", "w");

	fprintf(dotFile, "digraph Tree {\n");
	fprintf(dotFile, "\t rankdir=HR;\n");
	fprintf(dotFile, "\t node [shape=record];\n");

	if (DifferentiatorTree_DumpSubTree(startNode, dotFile) != DIF_TREE_NO_ERROR)
	{
		Logger_return(DIF_TREE_DUMP_ERROR);
	}

	fprintf(dotFile, "}\n");

	fclose(dotFile);

	system("dot Dumps\\Tree.dot -T png -o Dumps\\Tree.png");
	system("start Dumps\\Tree.png");

	return DIF_TREE_NO_ERROR;
}


DIF_TREE_ERRORS DifferentiatorTree_DumpSubTree(Node_t* currentNode, FILE* dotFile)
{
	Logger_assert(currentNode &&     "Node pointer is NULL in DifferentiatorTree_DumpSubTree()");
	Logger_assert(dotFile     && "Dot file pointer is NULL in DifferentiatorTree_DumpSubTree()");

	if (currentNode)
	{
		DifferentiatorTree_DumpNode(currentNode, dotFile);
	}

	else
	{
		Logger_return(DIF_TREE_DUMP_ERROR);
	}

	if (currentNode->left) 
	{
		DifferentiatorTree_DumpSubTree(currentNode->left, dotFile);
		fprintf(dotFile, "\t node%p:left -> node%p;\n", currentNode, currentNode->left);
	}

	if (currentNode->right) 
	{
		DifferentiatorTree_DumpSubTree(currentNode->right, dotFile);
		fprintf(dotFile, "\t node%p:right -> node%p;\n", currentNode, currentNode->right);
	}

	return DIF_TREE_NO_ERROR;
}


DIF_TREE_ERRORS DifferentiatorTree_DumpNode(Node_t* currentNode, FILE* dotFile)
{
	Logger_assert(currentNode && "Node pointer must not be NULL");
	Logger_assert(dotFile     && "file pointer must not be NULL");

	if (currentNode->type == TYPE_VAR)
	{
		fprintf(dotFile, "\t node%p [label=\"<left> left | { %c | %llu } | <right> right\"];\n", currentNode, (char) currentNode->value, currentNode->type);
	}

	else if (currentNode->type == TYPE_CONST)
	{
		fprintf(dotFile, "\t node%p [label=\"<left> left | { %llu | %llu } | <right> right\"];\n", currentNode, currentNode->value, currentNode->type);
	}

	else if (currentNode->type == TYPE_OP || currentNode->type == TYPE_NAMED_CONST || currentNode->type == TYPE_FUNC)
	{
		NodeValue_t dumpValue = currentNode->value;

		fprintf(dotFile, "\t node%p [label=\"<left> left | { %c", currentNode, (char) (dumpValue % 1000));
		dumpValue /= 1000;
		
		while (dumpValue > 0)
		{
			fprintf(dotFile, "%c", (char) (dumpValue % 1000));
			dumpValue /= 1000;
		}

		fprintf(dotFile, " | %llu } | <right> right\"];\n", currentNode->type);
	}

	else 
	{
		Logger_return(DIF_TREE_DUMP_ERROR);
	}

	return DIF_TREE_NO_ERROR;
}
