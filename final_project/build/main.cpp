#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Scan.h"
#include "Dictionary.h"
#include "ParseFile.h"
#include "Compile.h"
#include "decompile.h"

//TODO: change to relative path
#define DECOMPILED_VCXPROJ "C:/Users/ליבוביץ/Desktop/final_project/build/secure_application/secure_application.vcxproj"

using namespace std;
list<string> exeList;
list<string>::iterator it;
string origin_filepath, decompiled_filepath;
const string  API_KEY = KEY;

int main(int argc, char* argv[])
{
	
	exeList.push_back("C:\\Users\\User\\Desktop\\DevisionByZero.exe");
	scan("C:\\", "*.exe", exeList); // gets a list of all exe files 

	for (it = exeList.begin(); it != exeList.end(); it++)
	{
		//Print the contents
		//std::cout<< it->c_str() << std::endl;

		origin_filepath = it->c_str();
		decompiled_filepath = decompile(API_KEY, origin_filepath);
		defineDictionary();
		parseFile(g_dictionary, decompiled_filepath);

		//to test compilation use the following command:cmd /k "[filepath]"
		compile(DECOMPILED_VCXPROJ, origin_filepath);
		break;
	}
	
	system("pause");

	return 0;
}