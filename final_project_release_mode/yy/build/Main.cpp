#include <stdio.h>
#include <iostream>
#include "Dictionary.h"
#include "ParseFile.h"
#include "prog.h"
#include <iostream>
#include <fstream>
 
using namespace std;

int main(int argc, char* argv[])
{
	//change to enviorment variable
	const string  API_KEY = "834c39c3-3c97-469a-8433-0dc159038a8e";
	string decompiled_file=decompile(API_KEY,"C:\\Users\\ליבוביץ\\Desktop\\StackOverrun.exe");
	//cout << decompiled_file << "\n";
	defineDictionary();
	parseFile(g_dictionary, decompiled_file);

	return 0;
}