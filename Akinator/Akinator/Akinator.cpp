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


AKINATOR_ERRORS LoadDatabase(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");



	return AKINATOR_NO_ERROR;
}

AKINATOR_ERRORS UnloadDatabase(Akinator_t* akinator)
{
	Logger_assert(akinator && "Pointer must not be NULL");



	return AKINATOR_NO_ERROR;
}
