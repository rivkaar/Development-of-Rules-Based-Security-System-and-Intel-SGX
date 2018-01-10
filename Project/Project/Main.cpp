#include <stdio.h>
#include "Dictionary.h"
#include "ParseFile.h"
#include "SearchExe.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<windows.h>


int main(int argc, char* argv[])
{

	defineDictionary();
	parseFile(g_dictionary, "C:/Users/user/Desktop/sourceFile.c");

	return 0;
}
