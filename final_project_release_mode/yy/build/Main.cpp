#include <stdio.h>
#include <iostream>
#include "Dictionary.h"
#include "ParseFile.h"
#include "Compile.h"
#include "prog.h"
#include <iostream>
#include <fstream>
 
using namespace std;

int main(int argc, char* argv[])
{
	const string  API_KEY = KEY;
	string origin_filepath = "C:\\Users\\ליבוביץ\\Desktop\\StackOverrun.exe";
	string decompiled_filepath=decompile(API_KEY, origin_filepath);
	defineDictionary();
	parseFile(g_dictionary, decompiled_filepath);
	

	return 0;
}