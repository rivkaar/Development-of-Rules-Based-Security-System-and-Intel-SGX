#pragma once

#include <stdio.h>
#include <string>
#include <list>
#include "parsefile.h"

std::string getFuncName(std::string line);
bool isRecursive(std::string name, std::list<std::string> recursion_func);

