#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "Compile.h"

//void _tmain(int argc, TCHAR *argv[])
void compile(std:: string filepath)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//"C://Users//ליבוביץ//Desktop//StackOverrun.exe
	char cmdArgs[] = "C://Users//ליבוביץ//Desktop//StackOverrun.exe sarah";
	/*
	char params[]="sarah"
	char cmdArgs[]=strcat(filepath,params)

	*/

	/*if (argc != 2)
	{
	printf("Usage: %s [cmdline]\n", argv[0]);
	return;
	}*/

	// Start the child process. 
	if (!CreateProcess("C://Users//ליבוביץ//Desktop//StackOverrun.exe",   // No module name (use command line)
		cmdArgs,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
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

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
	
