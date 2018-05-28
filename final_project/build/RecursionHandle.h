#pragma once

#include <stdio.h>
#include <string>
#include <list>
#include "parsefile.h"

std::string getFuncName(std::string line);
bool isRecursive(std::string name, std::list<std::string> recursion_func);
void replaceToEnclaveRecursion(std::string line, std::ofstream* tempFile);
std::string addFunctionCallInWrapper(std::string funcName, std::list<std::string> params, int counter);

