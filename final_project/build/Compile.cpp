#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "Compile.h"
#include "decompile.h"
#define DEST_PATH

//renames the exe file and replaces the original exe file by this one??
void rename(std::string filepath, std::string origin_filepath) {
	int ret;
	//const char * oldname = filepath.c_str();
	const char * oldname = "C://Users//ליבוביץ//Desktop//final_project//build//x64//Release//Test.exe";
	//const char * newname = origin_filepath.c_str();

	const char * newname = "C://Users//ליבוביץ//Desktop//final_project//build//x64//Release//StackOverrun.exe";

	//delete the original file who has the suspected function
	//DeleteFile(oldname);

	//replace the original file with a file the contains the secure function
	ret = rename(oldname, newname);

	if (ret == 0) {
		printf("File renamed successfully");
	}
	else {
		printf("Error: unable to rename the file");
	}
	return;

}

void compile(std::string filepath, std::string origin_filepath)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	char cmdArgs[] = " 1234";

	/*if (argc != 2)
	{
	printf("Usage: %s [cmdline]\n", argv[0]);
	return;
	}*/

	// Start the child process. 
	//"C:/Users/ליבוביץ/Desktop/secure_functions/Debug/app.exe"
	if (!CreateProcess("C://Users//ליבוביץ//Desktop//final_project//build//x64//Release//Test.exe",   // No module name (use command line)
		cmdArgs,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,  // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);
	//renames the file and places it in the original fil
	rename(filepath, origin_filepath);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);




}

