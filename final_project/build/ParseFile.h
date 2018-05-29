#pragma once

#ifndef _PARSE_FILE_H
#define _PARSE_FILE_H

#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include "Dictionary.h"
#include <fstream>

void parseFile(std::map<std::string, std::string> dictionary, std::string sourceFilePath);
void findWordInLine(std::string line, int lineNum, std::ofstream* tempFile);
//void deleteLists();
void replaceLineInTempFile(std::string line, std::string str, int charNum, std::ofstream* tempFile);
std::list<std::string> getFuncParams(std::string func);
std::string getNewCallFunction(std::string oldFunctionName, std::list<std::string> params);

#endif // !_PARSE_FILE_H