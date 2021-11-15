/**
 * @defgroup   AKINATOR Akinator
 *
 * @brief      This file implements Akinator.
 *
 * @author     Stas
 * @date       2021
 */


#ifndef AKINATOR_H
#define AKINATOR_H


#define TX_USE_SPEAK

// #include <TXLib.h>

#include <string.h>

#include "../Tree/Tree.h"


const int MAX_QUESTION_STRING_LENGTH = 64;


typedef struct akinator_t {
	
	Tree_t* tree        = nullptr;
	Node_t* currentNode = nullptr;
	bool    voiceover   = false;

} Akinator_t;


enum AKINATOR_ERRORS {

	AKINATOR_NO_ERROR          = 0,
	UNABLE_TO_LOAD_DATABASE    = 1,
	INVALID_DATABASE_VALUE     = 2,
	DATABASE_DAMAGED           = 3,
};


enum AKINATOR_POISON_VALUES {

	AKINATOR_POISON_NUMBER   = 65000,
	AKINATOR_POISON_POINTER  = 666,
};


/**
 * @brief      Akinator constructor
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_Ctor(Akinator_t* akinator);


/**
 * @brief      Akinator destructor
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_Dtor(Akinator_t* akinator);


/**
 * @brief      Show "choose mode" massage
 */
void Akinator_ChooseModeMassage();



/**
 * @brief      Switch voiceover
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_SwitchVoiceover(Akinator_t* akinator);


/**
 * @brief      Gives description of a specific object
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_Find(Akinator_t* akinator);


/**
 * @brief      Compares two objects
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_Compare(Akinator_t* akinator);


/**
 * @brief      Normal akinator game
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_PlayGame(Akinator_t* akinator);


/**
 * @brief      Creates graph of a tree
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_DumpTree(Akinator_t* akinator);


/**
 * @brief      Loads the database
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_LoadDatabase(Akinator_t* akinator);


/**
 * @brief      Unloades the database
 *
 * @param      akinator  The akinator
 *
 * @return     The akinator errors
 */
AKINATOR_ERRORS Akinator_UnloadDatabase(Akinator_t* akinator);


/**
 * @brief      RENAME
 *
 * @param      currentNode  The current node
 * @param      database     The database
 *
 * @return     The akinator errors.
 */
AKINATOR_ERRORS Akinator_MakeTreeFromDatabase(Node_t** currentNode, FILE* database);


/**
 * @brief      DELETE
 *
 * @param      node  The node
 */
void Akinator_PrintNodes(Node_t* node);


/**
 * @brief      Creates new node
 *
 * @param[in]  nodeValue  The node value
 *
 * @return     New node pointer
 */
Node_t* Akinator_CreateNode(TreeElem_t nodeValue);


#endif // AKINATOR_H
