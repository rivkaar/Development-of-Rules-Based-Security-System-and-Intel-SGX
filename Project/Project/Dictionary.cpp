#include "Dictionary.h"

std::map<std::string, std::string> g_dictionary;

void defineDictionary()
{
	g_dictionary["strcpy"] = "enclaveStrcpy";
	g_dictionary["/"] = "enclaveDivideByZero";
	g_dictionary["main"] = "main";
	g_dictionary["int32_t"] = "int32_t";
}