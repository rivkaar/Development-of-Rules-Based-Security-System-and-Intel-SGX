#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Scan.h"
#include "Dictionary.h"
#include "ParseFile.h"
#include "Compile.h"
#include "decompile.h"


using namespace std;

int main(int argc, char* argv[])
{
	list<string> exeList;
	list<string>::iterator it;
	string origin_filepath, decompiled_filepath;
	exeList.push_back("C:\\Users\\ליבוביץ\\Desktop\\StackOverrun.exe");
	printf("Scanning your system.This might take a while ...\n");
	//scan("C:\\", "*.exe", exeList); // gets a list of all exe files 

	for (it = exeList.begin(); it != exeList.end(); it++)
	{
		origin_filepath = it->c_str();
		//Key refers to api key needed for decompilation
		decompiled_filepath = decompile(KEY, origin_filepath);
		defineDictionary();
		parseFile(g_dictionary, decompiled_filepath);
		//to test compilation use the following command:cmd /k "[filepath]"
		compile(DECOMPILED_VCXPROJ, origin_filepath);
		break;
	}
	system("pause");
	

	return 0;
}