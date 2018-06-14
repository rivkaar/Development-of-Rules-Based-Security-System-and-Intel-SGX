#include "parsefile.h"
#include "RecursionHandle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include <boost\algorithm\string.hpp>

#define  DLL  "#define ENCLAVE_FILE _T ("    "\""   ENCLAVE_DLL "\""           ")\n";
#define TEMP_FILE  SOLUTION_DIR "secure_application\\Source.cpp"

bool g_isComment = false;
bool isFunc = false;
bool isMain = false;
bool isRecursion = false;
bool isStopCondition = false;
std::string func_name, signatureLine, returnLine, conditionLine;
std::queue<char> q;
std::list<std::string> recursion_func;
std::string tail_recursion = "";
int counter = 0;

void findWordInLine(std::string line, int lineNum, std::ofstream* tempFile, std::fstream* securefunctionsFile)
{
	scanAndMap(line);
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
			if (c == '(')
			{
				std::string signature;
				if (line.at(len - 1) != ';' && !isCondition(line))
				{
					func_name = getFuncName(line);
					if (func_name != "") {
						isFunc = true;
						signatureLine = line;

					}
				}
				else
				{
					std::string name = isRecursive(line, recursion_func);

					if (boost::find_first(line, func_name + "(") && q.size() > 0 && func_name != "" && isFunc) {
						isRecursion = true;
						recursion_func.push_back(func_name);
						//lines to enable tail recursion
						tail_recursion = "\n" + replaceSignature(signatureLine) + "\n";
						tail_recursion += replaceCondition(conditionLine) + "\n{";
						//replacing normal recursive call to tail recursive call
						tail_recursion += "\n" + replaceTotTialCall(line) + "\n}";
						tail_recursion += "\n" + replaceStopCondition(signatureLine) + "\n" + "}";

						/*int pos_line = getPos(securefunctionsFile);
						(*securefunctionsFile).seekp(pos_line);
						std::cout << "pos: " << pos_line << std::endl;*/
						(*securefunctionsFile).seekp(628);
						(*securefunctionsFile) << tail_recursion;
						break;
					}

					else if (name != "") {
						bool contains_equal = false;
						//if the function in recursive list replace to enclaveRecursion
						//std::cout << line << " need to replace" << std::endl;
						if (line.find('=') != std::string::npos)
						{
							contains_equal = true;
						}
						std::string call_func = getCallFunc(line, name);
						std::list<std::string> params = getFuncParams(call_func);
						replaceToEnclaveRecursion(line, tempFile, contains_equal, call_func, getParams(params));
						isSuspiciousFuncFound = true;
						return;
					}

				}

			}
			if (str.compare("main") == 0)
			{
				isMain = true;
			}
			if (c == '{' && !isMain && isFunc) {
				q.push('{');
			}
			if (c == '}' && !isMain && isFunc) {
				q.pop();
			}
			if (isFunc  && isStopCondition && boost::find_first(line, "return"))
			{
				returnLine = line;
				isStopCondition = false;
			}

			if (isFunc && boost::find_first(line, "if"))
			{
				conditionLine = line;

			}

			if (g_dictionary.count(str) > 0)
			{
				int charNum = i - str.length();
				replaceLineInTempFile(line, str, charNum, tempFile);
				isSuspiciousFuncFound = true;
				return;
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
	//replacing vs backward trailing slash by forward slash
	std::string dll = DLL;
	std::string tempfilePath = TEMP_FILE;
	std::string securefunctionsPath = "C://Users//User//Desktop//final_project//build//secure_functions//secure_functions.cpp";

	std::replace(dll.begin(), dll.end(), '\\', '/');
	std::replace(tempfilePath.begin(), tempfilePath.end(), '\\', '/');

	std::ifstream sourceFile;
	std::ofstream tempFile;
	std::fstream securefunctionsFile;

	tempFile.open(tempfilePath);
	sourceFile.open(sourceFilePath);
	securefunctionsFile.open(securefunctionsPath, std::fstream::in | std::fstream::out);
	std::string line;
	int lineNum = 0;
	std::string str = "#pragma check_stack(off)\n";
	str += "#include \"sgx_urts.h\"\n";
	str += "#include \"secure_functions_u.h\"\n";
	str += "#include <tchar.h>\n";
	str += "#include <stdint.h>\n";
	str += "#include <stdio.h>\n";
	str += "#include <stdlib.h>\n";
	str += dll;
	str += "\nint* outRes = new int;\n";
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

	if (sourceFile.is_open() && tempFile.is_open() && securefunctionsFile.is_open())
	{
		tempFile << str;
		while (getline(sourceFile, line))
		{
			findWordInLine(line, lineNum, &tempFile, &securefunctionsFile);
			lineNum++;
		}

	}

	else
	{
		if (sourceFile.is_open() && securefunctionsFile.is_open())
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
	securefunctionsFile.close();
}


//void deleteLists()
//{
//	for (std::list<WordData*>::iterator list_iter = g_wordsList.begin(); list_iter != g_wordsList.end(); list_iter++)
//	{
//		delete *list_iter;
//	}
//}


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
	std::string p = "";
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
		else if (c == ')' && q.size() == 1)
		{
			params.push_back(p);
			q.pop();
		}
		else if (c == ')' && q.size() > 1)
		{
			q.pop();
			p += c;
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
	if (str.compare("strcpy") == 0) //replace all kinds of function
	{
		std::list<std::string> params = getFuncParams(line);
		std::string newLine = line.substr(0, charNum);
		newLine += getNewCallFunction(str, params) + ";\n";
		*tempFile << "//" + line + "\n";
		*tempFile << newLine;
	}
	else if (str.compare("/") == 0)//replace division by zero
	{
		std::string num1 = "";
		std::string num2 = "";
		std::string result = "";
		std::string type = "";
		std::string s = "";
		std::string newLine = "";
		char c;
		int counter = 0;
		bool isAfterEqualSign = false, isAfterNum1 = false, isAfterType = false, isPrintf = false;

		for (int i = 0; i < line.length(); i++)
		{
			c = line.at(i);
			if (c != ' ')
				s += line.at(i);
			if (!isAfterType && !isPrintf)
				type += c;
			if (s.compare("printf") == 0)
			{
				newLine += s;
				isPrintf = true;
				continue;
			}
			if (isPrintf)
			{
				if (c == ',')
					counter += 1;
				if (counter == 0)
					newLine += c;
				else if (counter == 1) {
					num1 += c;
					result = "";
					type = "";
				}
				else if (counter == 2)
					num2 += c;
				else if (counter > 2)
					break;
			}
			if (c == ' ' && !isAfterEqualSign && !isPrintf)
			{
				isAfterType = true;
				continue;
			}
			if (c == '=')
			{
				if (result == "") { //if the result has already been set 
					result = type;
					type = "";
				}

				isAfterEqualSign = true;
				continue;
			}
			else if (c == '/')
			{
				isAfterNum1 = true;
				continue;
			}
			else if (c == ';')
				break;

			if (isAfterEqualSign && !isAfterNum1 && c != '/' && !isPrintf)
				num1 += c;

			if (isAfterNum1 && c != ';' && !isPrintf)
				num2 += c;

			if (isAfterType && !isAfterEqualSign && !isAfterNum1 && !isPrintf)
				result += c;
		}
		if (isPrintf) {
			newLine += num1 + num2;
			newLine += ", enclaveDivideByZero(eid" + num1 + num2 + "," + "int result" + "));\n";
		}
		else {
			newLine += "enclaveDivideByZero(eid," + num1 + "," + num2 + "," + result + ");\n";
		}
		*tempFile << "//" + line + "\n";
		if (type != "")
			*tempFile << type + result + "\n";
		*tempFile << newLine;

	}
	else if (str.compare("int32_t") == 0)
	{
		int i;
		char c;
		int len = line.length();
		std::string paramName = "";
		bool isAfterEqualSign = false, isFunction = false;
		for (i = charNum + 7; i < len; i++)
		{
			c = line.at(i);
			if (c == '=')
			{
				isAfterEqualSign = true;
				break;
			}
			else if (c == ';')
			{
				break;
			}
			else if (!isAfterEqualSign && c == '*')
			{
				*tempFile << line + "\n";
				return;
			}
			else if (c == '(')
			{
				isFunction = true;
			}
		}
		if (isFunction)
		{
			*tempFile << line + "\n";
		}
		else
		{
			std::string newLine = line.substr(0, i);
			newLine += " = 0;\n";
			*tempFile << newLine;
		}
	}
}



