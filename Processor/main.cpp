/**
 * @file main.cpp
 */

#include <stdio.h>

#include "Processor.h"


int main(int argc, const char* argv[])
{

	File sourceCode = {};
	File_ctor(&sourceCode);

	writeSourceText(&sourceCode, "code.o", "a+");

	Processor intel_Core_i_5 = {};
	ProcessorCtor(&intel_Core_i_5);

	return 0;
}