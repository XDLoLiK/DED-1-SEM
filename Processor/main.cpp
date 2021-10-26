/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Terminal.h"


int main(void)
{
	bool running = true;

	while (running) {

		printf("%s", PATH);
		fflush(stdout);

		char command[MAX_PROCESS_NAME_LENGTH] = "";
		scanf(" %s", command);

		if (strcmp(command, "exit") == 0) 
			running = false;

		else if (strcmp(command, "fas") == 0) 
			ON_COMPILE()

		else if (strcmp(command, "go") == 0) 
			ON_EXECUTE()

		else if (strcmp(command, "nextdoor") == 0)
			ON_CHANGE_DIRECTORY()

		else if (strcmp(command, "help") == 0)
			ON_HELP()
		
		else 
			WARNING_LOG(INAPPROPRIATE_COMMAND);
	}

	return 0;
}
