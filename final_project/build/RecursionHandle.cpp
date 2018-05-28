#include "ParseFile.h"
#include "RecursionHandle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>

std::string getFuncName(std::string line) {

	std::istringstream f(line);
	std::string s, func_name;
	std::getline(f, s, '(');
	std::istringstream g(s);
	std::getline(g, s, ' ');
	std::getline(g, s, ' ');
	func_name = s;
	func_name.erase(std::remove(func_name.begin(), func_name.end(), '\t'), func_name.end());
	std::cout << func_name << " after get func name" << std::endl;

	return func_name;
}

bool isRecursive(std::string name, std::list<std::string> recursion_func) {
	bool exists = std::find(std::begin(recursion_func), std::end(recursion_func), name) != std::end(recursion_func);
	return exists;
}

void replaceToEnclaveRecursion(std::string line, std::ofstream* tempFile) {

	std::string newLine = "	enclaveRecursion(eid,(int*)outRes,sizeof(int));\n";
	*tempFile << "//" + line + "\n";
	*tempFile << newLine;

}
std::string addFunctionCallInWrapper(std::string funcName, std::list<std::string> params, int counter) {
	std::string str;
	str += "	case ";
	str += std::to_string(counter);
	str += ":" + funcName + "(";
	for (std::list<std::string>::iterator list_iter = params.begin(); list_iter != params.end(); list_iter++)
	{
		str += (*list_iter + ",");
	}
	str += ");break;\n";
	return str;
}
