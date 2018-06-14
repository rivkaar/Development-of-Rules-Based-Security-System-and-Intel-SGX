#pragma once

#include <stdio.h>
#include <string>
#include <list>
#include "parsefile.h"

void scanAndMap(std::string line);
std::string getFuncName(std::string line);
std::string isRecursive(std::string name, std::list<std::string> recursion_func);
bool isCondition(std::string name);
//void replaceToEnclaveRecursion(std::string line, std::ofstream* tempFile, bool contains_equal, std::string call_func);
void replaceToEnclaveRecursion(std::string line, std::ofstream* tempFile, bool contains_equal, std::string call_func, std::string params);
std::string getCallFunc(std::string line, std::string name);
std::string replacePrintf(std::string line, std::string call_func);
std::string replaceSignature(std::string signature);
std::string replaceStopCondition(std::string line);
std::string replaceTotTialCall(std::string recursiveCall);
std::string getParams(std::list<std::string> params);
int getPos(std::fstream* securefunctionFile);
std::string replaceCondition(std::string conditionLine);
