/*
 * @file Terminal.cpp
 */


#include "Terminal.h"


ERROR_CODES OnCompile() {

	File sourceFile = {};

	if (scanf(" %s.ass", sourceFile.path) != 1)	{
		RETURN(SCAN_ERROR);
	}

	if (IS_OK(File_ctor(&sourceFile))) {
		Compile(&sourceFile);
	}

	else {
		RETURN(COMPILATION_ERROR);
	}

	File_dtor(&sourceFile);

	RETURN(NO_ERROR);
}


ERROR_CODES OnDecompile() {										
																	
	char executablePath[MAX_EXECUTABLE_PATH_SIZE] = {};

	if (scanf(" %s.cum", executablePath) != 1) {
		RETURN(SCAN_ERROR);
	}

	else {
		Decompile(executablePath);
	}

	RETURN(NO_ERROR);
}


ERROR_CODES OnExecute() {  										

	Processor M1 = {};

	char executablePath[MAX_EXECUTABLE_PATH_SIZE] = "";

	if (scanf(" %s.cum", executablePath) != 1) {
		RETURN(SCAN_ERROR);
	}

	else {

		FILE* executableFile = fopen(executablePath, "rb");

		if (executableFile != nullptr) {						
																
			ProcessorCtor(&M1);				

			if (!IS_OK(Execute(&M1, executableFile))) {
				return EXECUTION_ERROR;
			}
			
			ProcessorDtor(&M1);									
		}														
																
		else 													
			RETURN(NO_SUCH_FILE_OR_DIRECTORY);		
	}

	RETURN(NO_ERROR);					
}	


void OnHelp() {														
																			
	printf("\n| ~COMPILATION~\n"											
		     "| - use fas compiler to compile .ass files\n" 				
		     "| ex. \"fas sample.ass\"\n\n"									
		     "| ~EXECUTION~\n"												
		     "| - use go command to execute .cum files\n"					
		     "| ex. \"go sample.cum\"\n\n"									
		     "| ~DECOMPILATION~\n"											
		     "| - use unfas to decompile .cum files\n"						
		     "| ex. \"unfas sample.cum\"\n\n"								
		     "| ~OTHERS~\n"													
		     "| - help to get help on programm's work\n"					
		     "| - exit to leave the terminal\n"								
		     "| - nextdoor to change directory\n\n");						
}		


ERROR_CODES OnChangeDirectory(char* path) {						
													
	char dir[MAX_DIRECTORY_SIZE] = "";				
	scanf(" %s", dir);								
													
	if (strcmp("..", dir) == 0) {
		GoBack(path);					
	}
													
	else {
		GoForward(path, dir);
	}

	RETURN(NO_ERROR);
}


ERROR_CODES GoBack(char* path) {										
															
	char* lastdir = strchr(path, '\\');						
															
	if (lastdir == nullptr) {								
		RETURN(YOU_ARE_ALREADY_ON_YOUR_KNEES);	
	}														
															
	else {													
															
		while (1) {											
															
			char* nextdir = strchr(lastdir + 1, '\\');		
															
			if (nextdir) 									
				lastdir = nextdir;							
			else											
				break;										
		}													
															
		*lastdir = '>';										
		*(lastdir + 1) = '\0';								
	}

	RETURN(NO_ERROR);
}


ERROR_CODES GoForward(char* path, char* directory) {					
												
	path[strlen(path) - 1] = '\\';				
	strcat(path, directory);					
	strcat(path, ">");

	RETURN(NO_ERROR);
}																	

