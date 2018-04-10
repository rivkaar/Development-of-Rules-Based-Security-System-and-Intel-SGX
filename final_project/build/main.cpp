#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Scan.h"
#include "Dictionary.h"
#include "ParseFile.h"
#include "Compile.h"
#include "decompile.h"

#define DECOMPILED_EXE "C://Users//ליבוביץ//Desktop//final_project//build//x64//Release//secure_application.exe"

using namespace std;


int main(int argc, char* argv[])
{
	//scan(std::string directory, std::string fileFilter, std::list<std::string> & list, bool recursively = true);
	const string  API_KEY = KEY;
	string origin_filepath = "C:\\Users\\ליבוביץ\\Desktop\\StackOverrun.exe";
	string decompiled_filepath = decompile(API_KEY, origin_filepath);
	defineDictionary();
	parseFile(g_dictionary, decompiled_filepath);
	//הבעיה פה שהוא שומר את הקובץ ההרצה הישן-הקוד הראשוני
	compile(DECOMPILED_EXE, origin_filepath);
	//to test compilation use the following command:cmd /k "[filepath]"
	system("pause");

	return 0;
}