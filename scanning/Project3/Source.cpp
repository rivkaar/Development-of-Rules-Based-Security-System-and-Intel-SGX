#include <windows.h>
#include <string>
#include <iostream>
#include <list>
#include "Access.h";

//retrieves list of exe files(with no administrator rights) of system
void GetFileListing(std::string directory, std::string fileFilter,std::list<std::string> & list, bool recursively = true)
{
	
	if (recursively)
		GetFileListing(directory, fileFilter,list, false);

	directory += "\\";

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE; 
	std::string fp;

	std::string filter = directory + (recursively ? "*" : fileFilter);

	hFind = FindFirstFile(filter.c_str(), &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	else
	{
		if (!recursively)
		{
			 fp = directory + std::string(FindFileData.cFileName);
			 //checking if there are administrator access rights to exe file,and if so not including the file in list
			 if (isAdmin(fp.c_str()))
			 {
				 list.push_back(fp);
			 }
		}

		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			if (!recursively)
			{
			
				 fp = directory + std::string(FindFileData.cFileName);
				 if (isAdmin(fp.c_str()))
				 {
					 list.push_back(fp);
				 }
			
				
			}
			else
			{
				if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)>0 && FindFileData.cFileName[0] != '.')
				{
					GetFileListing(directory + std::string(FindFileData.cFileName), fileFilter,list);
				}
			}
		}

		DWORD dwError = GetLastError();
		FindClose(hFind);
		if (dwError != ERROR_NO_MORE_FILES)
		{
			std::cout << "FindNextFile error. Error is " << dwError << std::endl;
		}
	}
	return;
}

int main(int argc, char* argv[])
{
	std::list<std::string> files;
	GetFileListing("C:\\", "*.exe", files);
	std::list<std::string>::iterator it;
	
	

	// Make iterate point to begining and incerement it one by one till it reaches the end of list.
	for (it = files.begin(); it != files.end(); it++)
	{
		//Print the contents
		std::cout << it->c_str()<< std::endl;

	}
	system("pause");
	return 0;
}
