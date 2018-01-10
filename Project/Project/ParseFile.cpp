#include "parsefile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

std::string TEMP_FILE = "C:/Users/user/Desktop/tempFile.c";
bool g_isComment = false;
bool isMain = false;
std::queue<char> q;
std::list<WordData*> g_wordsList;


WordData::WordData(int lineNum, int charNum, std::string word)
{
	WordData::lineNum = lineNum;
	WordData::charNum = charNum;
	WordData::word = word;
}

int WordData::getLineNum()
{
	return lineNum;
}
int WordData::getCharNum()
{
	return charNum;
}
std::string WordData::getWord()
{
	return word;
}


void findWordInLine(std::string line, int lineNum, std::ofstream* tempFile)
{

	std::string str = "";
	std::string newLine = "";
	bool isSuspiciousFuncFound = false;
	int len = line.length();

	for (int i = 0; i < len; i++)
	{
		char c = line.at(i);
		if (g_isComment)
		{
			if (c == '*' && i < (len - 1))
			{
				c = line.at(i + 1);
				if (c == '/')
				{
					g_isComment = false;
				}
				i++;
			}
		}
		else if (c == ' ' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || i == (len - 1))
		{
			if (isMain && c == '}')
			{
				q.pop();
				if (isMain && q.size() == 0)
				{
					*tempFile << "	if (SGX_SUCCESS != sgx_destroy_enclave(eid))\n";
					*tempFile << "	{\n";
					*tempFile << "		return -1; \n";
					*tempFile << "	}\n";
					isMain = false;
				}
			}
			else if (isMain && c == '{')
			{
				q.push('{');
				if (q.size() == 1) {
					*tempFile << line + "\n";
					*tempFile << "    sgx_status_t res = SGX_SUCCESS;\n";
					*tempFile << "	// Create the Enclave with above launch token.\n";
					*tempFile << "	res = createEnclave(&eid); \n";
					*tempFile << "    if (res != SGX_SUCCESS)\n	{\n";
					*tempFile << "		printf(\"App: error %#x, failed to create enclave.\", res); \n";
					*tempFile << "		return -1; \n	}\n";
					return;
				}

			}

			if (g_dictionary.count(str) > 0)
			{
				int charNum = i - str.length();
				WordData* data = new WordData(lineNum, charNum, str);
				g_wordsList.push_back(data);
				replaceLineInTempFile(line, str, charNum, tempFile);
				isSuspiciousFuncFound = true;
				return;
			}
			if (str.compare("main") == 0)
			{
				isMain = true;
				//	q.push('{');

			}
		}
		else if (c == '#')
		{
			break;
		}
		else if ((c == '/' && i < (len - 1) && line.at(i + 1) == '/') || (c == '/' && i < (len - 1) && line.at(i + 1) == '*'))
		{
			i++;
			c = line.at(i);
			if (c == '/')
			{
				break;
			}
			else if (c == '*')
			{
				g_isComment = true;
			}
			str = "";
		}
		else
		{
			if (c == '_' && i < (len - 1) && line.at(i + 1) == '_')
			{
				return;
			}
			str += line.at(i);
		}
		if (c == ' ')
			str = "";
	}

	if (!isSuspiciousFuncFound)
	{
		*tempFile << line + "\n";
	}
}

void parseFile(std::map<std::string, std::string> dictionary, std::string sourceFilePath)
{
	std::ifstream sourceFile;
	std::ofstream tempFile;
	tempFile.open(TEMP_FILE);
	sourceFile.open(sourceFilePath);
	std::string line;
	int lineNum = 0;
	std::string str = "#pragma check_stack(off)\n";
	str += "#include \"stdafx.h\"\n";
	str += "#include \"sgx_urts.h\"\n";
	str += "#include \"SecureFunctions_u.h\"\n";
	str += "#include <tchar.h>\n";
	str += "#include <stdint.h>\n";
	str += "#include <stdio.h>\n";
	str += "#include <stdlib.h>\n";
	str += "#define ENCLAVE_FILE _T(\"SecureFunctions.signed.dll\")\n";
	str += "using namespace std;\n";
	str += "/* OCall functions */\n";
	str += "void ocall_print_string(const char *str)\n{\n";
	str += "	/* Proxy/Bridge will check the length and null-terminate\n";
	str += "	* the input string to prevent buffer overflow.\n";
	str += "	*/\n";
	str += "	printf(\"%s\", str);\n}\n";
	str += "sgx_status_t createEnclave(sgx_enclave_id_t *eid) {\n";
	str += "	sgx_status_t		ret = SGX_SUCCESS;\n";
	str += "	sgx_launch_token_t	token = { 0 };\n";
	str += "	int					updated = 0; \n";
	str += "	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, eid, NULL); \n";
	str += "	return ret;\n}\n";
	str += "sgx_enclave_id_t eid;\n\n";

	if (sourceFile.is_open() && tempFile.is_open())
	{
		tempFile << str;
		while (getline(sourceFile, line))
		{
			findWordInLine(line, lineNum, &tempFile);
			lineNum++;
		}

	}

	else
	{
		if (sourceFile.is_open())
		{
			std::cout << "Unable to open temp file";
		}
		else
		{
			std::cout << "Unable to open source file";
		}
	}
	sourceFile.close();
	tempFile.close();

	copyToSourceFile("C:/Users/user/Desktop/sourceFile.c"); //Copies all content back to the source file
}


void deleteLists()
{
	for (std::list<WordData*>::iterator list_iter = g_wordsList.begin(); list_iter != g_wordsList.end(); list_iter++)
	{
		delete *list_iter;
	}
}


std::string getNewCallFunction(std::string oldFunctionName, std::list<std::string> params)
{
	std::string newCallFunc = "";
	newCallFunc += g_dictionary[oldFunctionName];
	newCallFunc += "(eid, ";
	for (std::list<std::string>::iterator list_iter = params.begin(); list_iter != params.end(); list_iter++)
	{
		newCallFunc += (*list_iter + ",");
	}
	newCallFunc.pop_back();
	newCallFunc += ')';
	printf("%s\n", newCallFunc);
	return newCallFunc;
}


std::list<std::string> getFuncParams(std::string func)
{
	std::queue<char> q;
	std::list<std::string> params;
	std::string p;
	for (int i = 0; i < func.length(); i++)
	{
		char c = func.at(i);
		if (c == '(')
		{
			if (q.size() != 0)
			{
				p += c;
			}
			q.push(c);
		}
		else if (c == ')')
		{
			params.push_back(p);
			q.pop();
		}
		else if (c == ',')
		{
			params.push_back(p);
			printf("%s\n", p);
			p = "";
		}
		else if (q.size() != 0)
		{
			p += c;
		}
		else //if it is before the start of parse the params func
		{
			continue;
		}
		if (q.size() == 0)
		{
			return params;
		}
	}
	return params;
}

void replaceLineInTempFile(std::string line, std::string str, int charNum, std::ofstream* tempFile)
{
	std::list<std::string> params = getFuncParams(line);
	std::string newLine = line.substr(0, charNum);
	newLine += getNewCallFunction(str, params) + ";\n";
	*tempFile << "//" + line + "\n";
	*tempFile << newLine;
}

void copyToSourceFile(std::string sourceFilePath)
{
	std::ifstream tempFile;
	std::ofstream sourceFile;
	tempFile.open(TEMP_FILE);
	sourceFile.open(sourceFilePath);
	std::string line;
	if (sourceFile.is_open() && tempFile.is_open())
	{
		while (getline(tempFile, line))
		{
			sourceFile << line + "\n";
		}
	}
	else
	{
		if (sourceFile.is_open())
		{
			std::cout << "Unable to open temp file";
		}
		else
		{
			std::cout << "Unable to open source file";
		}
	}

	sourceFile.close();
	tempFile.close();
}
