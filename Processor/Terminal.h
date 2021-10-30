/**
* @file ProcessorConfig.h
*/


#ifndef PROCESSOR_CONFIG_H
#define PROCESSOR_CONFIG_H


#include <string.h>

#include "../general/Errors.h"

#include "Processor.h"
#include "Assembler.h"
#include "Disassembler.h"


const int MAX_PROCESS_NAME_LENGTH = 12;
const int MAX_CD_PATH_SIZE 		  = 256;
const int MAX_DIRECTORY_SIZE 	  = 32;


static char PATH[MAX_CD_PATH_SIZE] = "DedProjects\\Processor>";


#define ON_COMPILE() {												\
																	\
	File sourceFile = {};											\
																	\
	if (scanf(" %s.ass", sourceFile.path) != 1)						\
		WARNING_LOG(SCAN_ERROR, ERROR);								\
																	\
	if (IS_OK(File_ctor(&sourceFile)))		 						\
		Compile(&sourceFile);										\
																	\
	File_dtor(&sourceFile);											\
}


#define ON_EXECUTE() {  										\
																\
	Processor M1 = {};											\
																\
	char executablePath[MAX_PATH_SIZE] = "";					\
																\
	if (scanf(" %s.cum", executablePath) != 1) {				\
		WARNING_LOG(SCAN_ERROR, ERROR);							\
	}															\
																\
	else {														\
																\
		FILE* executableFile = fopen(executablePath, "r");		\
																\
		if (executableFile != nullptr) 							\
			Execute(&M1);										\
																\
		else 													\
			WARNING_LOG(NO_SUCH_FILE_OR_DIRECTORY, ERROR);		\
	}															\
}						   	


#define ON_CHANGE_DIRECTORY() {						\
													\
	char dir[MAX_DIRECTORY_SIZE] = "";				\
	scanf(" %s", dir);								\
													\
	if (strcmp("..", dir) == 0)		 				\
		GO_BACK()									\
													\
	else 											\
		GO_FORWARD(dir)								\
}


#define GO_BACK() {											\
															\
	char* lastdir = strchr(PATH, '\\');						\
															\
	if (lastdir == nullptr) {								\
		WARNING_LOG(YOU_ARE_ALREADY_ON_YOUR_KNEES, ERROR);	\
	}														\
															\
	else {													\
															\
		while (1) {											\
															\
			char* nextdir = strchr(lastdir + 1, '\\');		\
															\
			if (nextdir) 									\
				lastdir = nextdir;							\
			else											\
				break;										\
		}													\
															\
		*lastdir = '>';										\
		*(lastdir + 1) = '\0';								\
	}														\
}


#define GO_FORWARD(directory) {					\
												\
	PATH[strlen(PATH) - 1] = '\\';				\
	strcat(PATH, directory);					\
	strcat(PATH, ">");							\
}


#define ON_HELP() {															\
																			\
	printf("\n| ~COMPILATION~\n"											\
		     "| - use fas compiler to compile .ass files\n" 				\
		     "| ex. \"fas sample.ass\"\n\n"									\
		     "| ~EXECUTION~\n"												\
		     "| - use go command to execute .cum files\n"					\
		     "| ex. \"go sample.cum\"\n\n"									\
		     "| ~DECOMPILATION~\n"											\
		     "| - use unfas to decompile .cum files\n"						\
		     "| ex. \"unfas sample.cum\"\n\n"								\
		     "| ~OTHERS~\n"													\
		     "| - help to get help on programm's work\n"					\
		     "| - exit to leave the terminal\n"								\
		     "| - nextdoor to change directory\n\n");						\
}																			


#endif // PROCESSOR_CONFIG_H
