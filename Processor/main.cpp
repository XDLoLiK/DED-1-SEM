/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Terminal\Terminal.h"


int main(void)
{
	char PATH[MAX_CD_PATH_SIZE] = "DedProjects\\Processor>";

	bool running = true;

	while (running) {

		printf("%s", PATH);
		fflush(stdout);

		char command[MAX_PROCESS_NAME_LENGTH] = "";
		scanf(" %s", command);

		if (strcmp(command, "zzz") == 0) 
			running = false;

		else if (strcmp(command, "fas") == 0) 
			OnCompile();
      													
		else if (strcmp(command, "dick") == 0) 			
			OnDecompile();

		else if (strcmp(command, "go") == 0) 
			OnExecute();

		else if (strcmp(command, "nextdoor") == 0)
			OnChangeDirectory(PATH);

		else if (strcmp(command, "help") == 0)
			OnHelp();
		
		else 
			WARNING_LOG(INAPPROPRIATE_COMMAND, ERROR);
	}

	return 0;
}
