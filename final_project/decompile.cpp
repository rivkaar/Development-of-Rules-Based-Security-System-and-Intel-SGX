#include <iostream>
#include <retdec/retdec.h>
#include <fstream>
#include "./build/decompile.h"
#include <string.h>
#include <sstream>
#include <vector>

using namespace retdec;


std::string parseName(std::string filepath) {
	std::string copy = filepath;
	std::istringstream f(copy);
	std::string s, exe_name,c_name="./files/";
	while (std::getline(f, s, '\\')) {
		exe_name = s;
	}
	std::istringstream g(exe_name);
	while (std::getline(g, s, '.')) {
		c_name += s; break;
	}
	c_name += ".c";
	return c_name;


}

std:: string decompile(std::string API_KEY,std:: string FILE_PATH) {
	/*if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " API-KEY FILE\n";
		return 1;
	}*/
	std::string output_filepath = parseName(FILE_PATH);
	std::ofstream fs(output_filepath);
	
	try {
		Decompiler decompiler(
			Settings()
				.apiKey(API_KEY)
		);
		auto decompilation = decompiler.runDecompilation(
			DecompilationArguments()
				.mode("bin")
				.inputFile(File::fromFilesystem(FILE_PATH))
		);
		decompilation->waitUntilFinished();
		//std::cout << decompilation->getOutputHll();
		fs << decompilation->getOutputHll();
		return output_filepath;
		} catch (const Error &ex) {
		std::cerr << "error: " << ex.what() << "\n";
		return NULL;
	}
}
