/**
 * @defgroup   AKINATOR Akinator
 *
 * @brief      This file implements Akinator.
 *
 * @author     Stas
 * @date       2021
 */


#include "Akinator.h"


AKINATOR_ERRORS Akinator_Ctor(Akinator_t* akinator)
{
	Logger_assert(akinator && "Inappropriate akinator pointer");

	Tree_t* treeAkinator = (Tree_t*) calloc(1, sizeof (Tree_t));
	
	Logger_assert(treeAkinator && "Tree pointer is NULL");

	Tree_Ctor(treeAkinator, "Something");

	akinator->tree        = treeAkinator; 
	akinator->currentNode = akinator->tree->root;

	Akinator_LoadDatabase(akinator);
	
	Akinator_PrintNodes(akinator->tree->root);

	return AKINATOR_NO_ERROR;
}


AKINATOR_ERRORS Akinator_Dtor(Akinator_t* akinator)
{
	Logger_assert(akinator && "Inappropriate akinator pointer");

	Tree_Dtor(akinator->tree);

	akinator->currentNode = (Node_t*) AKINATOR_POISON_POINTER;

	return AKINATOR_NO_ERROR;
}


void Akinator_ChooseModeMassage()
{
	printf("\nChoose your fighter:\n\n"
		   "\t-1: Exit\n"
		   "\t 0: Normal mode\n"
		   "\t 1: Give definition\n"
		   "\t 2: Compare mode\n"
		   "\t 3: Create data base graph\n"
		   "\t 4: Switch voiceover\n\n");
}


AKINATOR_ERRORS Akinator_SwitchVoiceover(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");

	akinator->voiceover = 1 - akinator->voiceover;

	return AKINATOR_NO_ERROR;
}


AKINATOR_ERRORS Akinator_Find(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");



	return AKINATOR_NO_ERROR;
}


AKINATOR_ERRORS Akinator_Compare(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");



	return AKINATOR_NO_ERROR;
}


AKINATOR_ERRORS Akinator_PlayGame(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");



	return AKINATOR_NO_ERROR;
}


AKINATOR_ERRORS Akinator_DumpTree(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");



	return AKINATOR_NO_ERROR;
}


AKINATOR_ERRORS Akinator_LoadDatabase(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");

	FILE* database = fopen("Akinator.database", "r");

	if (database == nullptr)
		Logger_return(UNABLE_TO_LOAD_DATABASE);

	Akinator_MakeTreeFromDatabase(&(akinator->tree->root), database);

	fclose(database);

	return AKINATOR_NO_ERROR;
}


AKINATOR_ERRORS Akinator_MakeTreeFromDatabase(Node_t** currentNode, FILE* database)
{
	char symbol = (char) fgetc(database);

	while (symbol != EOF) {

		if (symbol == '{')
			break;

		if (symbol == '}')
			return AKINATOR_NO_ERROR;

		symbol = (char) fgetc(database);
	}

	if (symbol == EOF)
		Logger_return(DATABASE_DAMAGED);

	char value[MAX_QUESTION_STRING_LENGTH] = "";
	int  count = 0;

	fscanf(database, " \"%[^\"]\" %n", value, &count);

	if (count)
		*currentNode = Akinator_CreateNode(value);
	else
		Logger_return(INVALID_DATABASE_VALUE);

	Akinator_MakeTreeFromDatabase(&(*currentNode)->left,  database);
	Akinator_MakeTreeFromDatabase(&(*currentNode)->right, database);
}


Node_t* Akinator_CreateNode(TreeElem_t nodeValue)
{
	Logger_assert(nodeValue && "Invalid value");

	Node_t* newNode = (Node_t*) calloc(1, sizeof (Node_t));

	if (!newNode) {
		return nullptr;
	}

	newNode->value = (char*) calloc(MAX_QUESTION_STRING_LENGTH, sizeof (char));
	strcpy(newNode->value, nodeValue);

	newNode->right = nullptr;
	newNode->left  = nullptr;

	return newNode;
}



void Akinator_PrintNodes(Node_t* node)
{
	printf("%s\n", node->value);

	if (!node)
		return;

	if (node->left)
		Akinator_PrintNodes(node->left);

	if (node->right)
		Akinator_PrintNodes(node->right);
}


AKINATOR_ERRORS Akinator_UnloadDatabase(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");

	FILE* database = fopen("Akinator.database", "w");



	return AKINATOR_NO_ERROR;
}



