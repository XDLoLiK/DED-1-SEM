/**
* @file main_asm.cpp
*/


#include "Assembler.h"


int main(void)
{
	File sourceFile = {};											
																	
	if (scanf(" %s.ass", sourceFile.path) != 1) {						
	
		WARNING_LOG(SCAN_ERROR);
		return 0;
	}					
																	
	if (IS_OK(File_ctor(&sourceFile))) {						
																	
		FILE* executableFile = CreateExecutable(sourceFile.path);	
		
		if (!IS_OK(Compile(&sourceFile, executableFile))) {
			
			WARNING_LOG(COMPILATION_ERROR);
			return 0;
		 } 						
	}																
																	
	File_dtor(&sourceFile);

	return 0;
}
		