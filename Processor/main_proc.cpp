/**
* @file main_proc.cpp
*/


#include "Processor.h"


int main(void)
{
	Processor M1 = {};											
																
	char executablePath[MAX_PATH_SIZE] = "";					
																
	if (scanf(" %s.cum", executablePath) != 1) {				
		
		WARNING_LOG(SCAN_ERROR);	
		return 0;							
	}															
																
	else {														
																
		FILE* executableFile = fopen(executablePath, "r");		
																
		if (executableFile != nullptr) {						
																
			M1.codes = GetCodes(executableFile);				

			if (!IS_OK(Execute(&M1))) {

				WARNING_LOG(EXECUTION_ERROR);
				return 0;
			}
		}														
																
		else {		

			WARNING_LOG(NO_SUCH_FILE_OR_DIRECTORY);
			return 0;	
		}														
	}															
	
	return 0;
}
