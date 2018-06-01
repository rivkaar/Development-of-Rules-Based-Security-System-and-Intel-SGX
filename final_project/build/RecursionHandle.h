#pragma once

#include <stdio.h>
#include <string>
#include <list>
#include "parsefile.h"

void scanAndMap(std::string line);
std::string getFuncName(std::string line);
bool isRecursive(std::string name, std::list<std::string> recursion_func);
bool isCondition(std::string name);
void replaceToEnclaveRecursion(std::string line, std::ofstream* tempFile, bool contains_equal);
std::string addFunctionCallInWrapper(std::string funcName, std::list<std::string> params, int counter);


