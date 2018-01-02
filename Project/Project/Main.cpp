#include <stdio.h>
#include <iostream>
#include "Dictionary.h"
#include "ParseFile.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	defineDictionary();
	parseFile(g_dictionary, "C:/Users/user/Desktop/test_befor.c", "C:/Users/user/Desktop/test_after.c");

	return 0;
}