#include "SearchExe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include<stdio.h>
#include<stdlib.h>

#using <mscorlib.dll>
using namespace System;
using namespace System::IO;
using namespace std;

map<string, string> g_executeFilesFullPath;
list<string> g_executeFilesList;

struct Node {
	string dir;
	Node* left;
	Node* right;
};

Node* GetNewNode(string dir) {
	Node* newNode = new Node();
	newNode->dir = dir;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* Insert(Node* rootPtr, string dir) {
	if (rootPtr == NULL) {
		rootPtr = GetNewNode(dir);
		return rootPtr;
	}
	else if (dir <= rootPtr->dir) {
		rootPtr->left = Insert(rootPtr->left, dir);
	}
	else {
		rootPtr->right = Insert(rootPtr->right, dir);
	}
	return rootPtr;
}
using System::IntPtr;
using System::Runtime::InteropServices::Marshal;


void findAllExecuteFiles()
{

	string path[50];
	String^ fullPath = "C:\\";
	string fileName;
	string dirName;
	Node* rootPtr = NULL;

	//Find the subfolders in the folder that is passed in.
	cli::array<String^>^directories = Directory::GetDirectories(fullPath);
	int numDirs = directories->Length;

	IntPtr ip = Marshal::StringToHGlobalAnsi(directories[2]);
	dirName = static_cast<const char*>(ip.ToPointer());
	Marshal::FreeHGlobal(ip);

	rootPtr = Insert(rootPtr, dirName);

	for (int i = 0; i < numDirs; i++)
	{
		//^fullPath += dirName;
		//cli::array<String^>^directories = Directory::GetDirectories(fullPath+ dirName);
	}
	

	for (int i = 0; i < numDirs; i++)
	{

		// Find all the exe files in the subfolder.
		//cli::array<System::String ^>^ f = Directory::GetFiles(directories[i], "*.exe");
		//if (f->Length != 0)
			//Console::WriteLine(f[0]);
	}





	//search exe file

	// Find the subfolders in the folder that is passed in.
	/*cli::array<System::String ^>^directories = Directory::GetDirectories("C:\\");
	int numDirs = directories->Length;

	for (int i = 0; i < numDirs; i++)
	{
	// Find all the exe files in the subfolder.
	cli::array<System::String ^>^ f = Directory::GetFiles(directories[i], "*.exe");
	if (f->Length != 0)
	Console::WriteLine(f[0]);
	}*/

	//fullPath += path[i];
	//fullPath += '\\';

	//g_executeFilesFullPath[fileName] = fullPath;
	//g_executeFilesList.push_back(fileName);


}
