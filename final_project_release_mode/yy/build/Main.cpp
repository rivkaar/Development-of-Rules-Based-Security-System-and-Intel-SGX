#include <stdio.h>
#include <iostream>
#include "Scan.h"
#include "Dictionary.h"
#include "ParseFile.h"
#include "Compile.h"
#include "prog.h"
#include <iostream>
#include <fstream>
 
using namespace std;


int main(int argc, char* argv[])
{
	//scan();
	const string  API_KEY = KEY;
	string origin_filepath = "C:\\Users\\ליבוביץ\\Desktop\\StackOverrun.exe";
	string decompiled_filepath=decompile(API_KEY, origin_filepath);
	defineDictionary();
	parseFile(g_dictionary, decompiled_filepath);
	compile(decompiled_filepath,origin_filepath);
	//system("pause");

	return 0;
}