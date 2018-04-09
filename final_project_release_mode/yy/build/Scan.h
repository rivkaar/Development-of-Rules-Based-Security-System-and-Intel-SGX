#pragma once
#include <string>
#include <list>

void scan(std::string directory, std::string fileFilter, std::list<std::string> & list, bool recursively = true);