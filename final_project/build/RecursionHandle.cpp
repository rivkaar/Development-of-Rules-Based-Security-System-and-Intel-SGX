#include "Parsefile.h"
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
