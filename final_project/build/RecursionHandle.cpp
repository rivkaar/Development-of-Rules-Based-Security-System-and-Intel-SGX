#include "ParseFile.h"
#include "RecursionHandle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include <boost\algorithm\string.hpp>

//HashMap to hold variblename->value
std::map<std::string, std::string> variableMap;


//preprocessor macro ??
//#define KEY(name) #name
//#define VALUE(name) name

void addMapEntry(std::string key,std::string value)
{
	variableMap[key] = value;
	std::cout << "key:" << key << " val:" << variableMap[key] << std::endl;
}

void scanAndMap(std::string line)
{
	if (line.find('=') != std::string::npos)
	{
		std::cout << "line " << line << "\n";
		std::string s,key,value;
		std::istringstream g(line);
		std::getline(g, s, '=');
		std::string temp = s;
		std::istringstream f(temp);
		while (std::getline(f, s, ' ')){
			key = s;
		}
		boost::trim_left(key);
		std::getline(g, s, '=');
		temp= s;
		std::istringstream a(temp);
		std::getline(a, s, ';');
		value = s;
		addMapEntry(key, value);


	}
}

std::string getFuncName(std::string line) {
	std::istringstream f(line);
	std::string s, func_name, test;

	std::getline(f, s, '(');

	//if there is a equal sign, need to check if there is no function call after the equal sign
	if (s.find('=') != std::string::npos)
	{
		std::istringstream g(s);
		std::cout << "line with eq" << s << std::endl;
		while (std::getline(g, s, '=')) {}
		std::cout << "line after removing eq" << s << std::endl;
	}
	std::istringstream a(s);
	std::getline(a, s, ' ');
	std::getline(a, s, ' ');
	func_name = s;
	func_name.erase(std::remove(func_name.begin(), func_name.end(), '\t'), func_name.end());
	if (func_name != "")
		std::cout << " after get func name: " << func_name << std::endl;
	return func_name;
}

bool isRecursive(std::string name, std::list<std::string> recursion_func) {
	bool exists = std::find(std::begin(recursion_func), std::end(recursion_func), name) != std::end(recursion_func);
	return exists;
}																			

void replaceToEnclaveRecursion(std::string line, std::ofstream* tempFile ,bool contains_equal) {

	//These lines are required in order to get a return value from inside the enclave
	std::string replacement_lines= "\tint* outRes = new int;\n\t*outRes = 0;\n\t";
	//Replace unsecure recursive function with a secure recursive function
	replacement_lines += "enclaveRecursive(eid,(int*)outRes,sizeof(int));\n";
	if (contains_equal)
	{
		//here we need to get the variable from the right of the line
		std::string assignment_variable;
		std::istringstream g(line);
		std::getline(g, assignment_variable, '='); 
		//in case the recursion return value was assigned to to a variable 
		replacement_lines += assignment_variable + "= *outRes;\t//" + line + "\n";
	}
	*tempFile << replacement_lines;

}
std::string addFunctionCallInWrapper(std::string funcName, std::list<std::string> params, int counter) {
	std::string str;
	str += "	case ";
	str += std::to_string(counter);
	str += ":" + funcName + "(";
	for (std::list<std::string>::iterator list_iter = params.begin(); list_iter != params.end(); list_iter++)
	{
		
		if (variableMap.find(*list_iter) != variableMap.end())
		{
			str += (variableMap[*list_iter] + ",");
		}
		else
		{
			str += (*list_iter + ",");
		}
	}
	str += ");break;\n";
	return str;
}

