#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "Compile.h"
#include "decompile.h"


std::string findExe(std::string filepath)
{
	//getting directory path
	size_t found = filepath.find_last_of("/\\");
	std::string dir=filepath.substr(0, found);
	return dir;
}

void rename(std::string filepath, std::string origin_filepath) {
	int ret;
	const char * oldname = filepath.c_str();
	const char * newname = origin_filepath.c_str();

	//delete the original file who has the suspected function
	DeleteFile(newname);

	//replace the original file with a file the contains the secure function
	ret = rename(oldname, newname);

	if (ret == 0) {
		printf("File renamed successfully\n");
	}
	else {
		printf("Error: unable to rename the file\n");
	}
	return;

}

void compile(std::string filepath, std::string origin_filepath)
{

		
		/*std::cout << findExe(filepath) << "\n";
		system("pause");*/
		std:: string cmd= "cd C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin & vcvars32.bat & cd C:/Program Files (x86)/IntelSWTools/parallel_studio_xe_2018.1.041/bin & psxevars.bat intel64 vs2015 & msbuild /p:useenv=true /p:Configuration=Release /p:Platform=x64 /t:Rebuild ";
		cmd += filepath;
		
		//system recieves const char*
		system(cmd.c_str());
	
		system("pause");
		//renames the exe file and replaces the original exe file by this one??
		//TODO:rename functionality not perfect,and how to set as reach file?
		//rename(filepath, origin_filepath);
		



}

