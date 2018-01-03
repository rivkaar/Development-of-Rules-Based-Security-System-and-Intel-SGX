#pragma once

#ifndef _PARSE_FILE_H
#define _PARSE_FILE_H

#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include "Dictionary.h"
#include <fstream>


class WordData
{
private:
	int lineNum;
	int charNum; // the location in the start of the word in the line
	std::string word;
public:
	WordData(int lineNum, int charNum, std::string word);
	int getLineNum();
	int getCharNum();
	std::string getWord();
};

extern std::list<WordData*> g_wordsList;
extern std::list<std::string> g_executeFilesList;
extern std::map<std::string, std::string> g_executeFilesFullPath;

void parseFile(std::map<std::string, std::string> dictionary, std::string inputFilePath, std::string outputFilePath);
void findWordInLine(std::string line, int lineNum, std::ofstream* outputFile);
void findAllExecuteFiles(std::string executeFilesListPath);
void deleteLists();
void replaceLineInOutputFile(std::string line, std::string str, int charNum, std::ofstream* outputFile);
#endif // !_PARSE_FILE_H
