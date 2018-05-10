#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <algorithm>

void replace_file(std::string oldName, std::string newName)
{
	int ret = rename(oldName.c_str(), newName.c_str());

	if (ret == 0) {
		printf("File renamed successfully\n");
	}
	else {
		printf("Error: unable to rename the file\n");
	}
	return;
}

//'converts' exe file to txt in order to deactivate the original file
void deactivate(std::string origin_filepath)
{
	std::string txt_filepath = origin_filepath;
	std::string exe = "exe";
	txt_filepath.replace(txt_filepath.find(exe), exe.length(), "txt");
	replace_file(origin_filepath, txt_filepath);
	return;

}


void compile(std::string filepath, std::string origin_filepath)
{


	std::string cmd = "cd C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin & vcvars32.bat & \
			 cd C:/Program Files (x86)/IntelSWTools/parallel_studio_xe_2018.1.041/bin &\
			 psxevars.bat intel64 vs2015 &\
			 msbuild /p:useenv=true /p:Configuration=Release /p:Platform=x64 /t:Rebuild ";
	cmd += filepath;
	//calling msbuild command
	system(cmd.c_str());
	deactivate(origin_filepath);
	//replaces decompiled exe in original exe filepath
	replace_file(EXE_FILEPATH, origin_filepath);
	system("pause");

}

