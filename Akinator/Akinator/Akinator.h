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

#include "../Tree/Tree.h"


typedef struct akinator_t {
	
	Tree_t* tree        = nullptr;
	Node_t* currentNode = nullptr;
	bool    voiceover   = false;

} Akinator_t;


enum AKINATOR_ERRORS {

	AKINATOR_NO_ERROR = 0,
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


#endif // AKINATOR_H
