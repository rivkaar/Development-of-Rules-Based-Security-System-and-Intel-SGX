#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Scan.h"
#include "Dictionary.h"
#include "ParseFile.h"
#include "Compile.h"
#include "decompile.h"
#include <windows.h> // WinApi header

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string filePath = "C:/Users/User/Desktop/final_project/build/files/factorial.c";
	list<string> exeList;
	list<string>::iterator it;
	string origin_filepath, decompiled_filepath;
	exeList.push_back("C:\\Users\\User\\Desktop\\factorial.exe");
	//printf("Scanning your system.This might take a while ...\n");
	//scan("C:\\", "*.exe", exeList); // gets a list of all exe files 

	for (it = exeList.begin(); it != exeList.end(); it++)
	{
	//	origin_filepath = it->c_str();
	//Key refers to api key needed for decompilation
	//SetConsoleTextAttribute(hConsole, 10);
	//std::cout << "decompiling your file...";
	//decompiled_filepath = decompile(KEY, origin_filepath);
	SetConsoleTextAttribute(hConsole, 15);
	defineDictionary();
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "parsing your file...";
	SetConsoleTextAttribute(hConsole, 15);
	parseFile(g_dictionary, filePath);
	////to test compilation use the following command:cmd /k "[filepath]"
	//SetConsoleTextAttribute(hConsole, 15);
	//std::cout << "compiling the file\n";
	//SetConsoleTextAttribute(hConsole, 10);
	//compile(DECOMPILED_VCXPROJ, origin_filepath);
		break;
	}

	system("pause");
	return 0;
}

