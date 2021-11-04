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
			ON_COMPILE();
      													// rename
		else if (strcmp(command, "dick") == 0) 			// refactor execute (without go)
			ON_DECOMPILE();

		else if (strcmp(command, "go") == 0) 
			ON_EXECUTE();

		else if (strcmp(command, "nextdoor") == 0)
			ON_CHANGE_DIRECTORY(PATH);

		else if (strcmp(command, "help") == 0)
			ON_HELP();
		
		else 
			WARNING_LOG(INAPPROPRIATE_COMMAND, ERROR);
	}

	return 0;
}
