#include <iostream>
#include <retdec/retdec.h>
#include <fstream>

using namespace retdec;

int main(int argc, char **argv) {

	//added output file:

	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " API-KEY FILE\n";
		return 1;
	}
	std::ofstream fs("output.c");
	if (!fs)
	{
		std::cerr << "Cannot open the output file." << std::endl;
		return 1;
	}
	


	try {
		Decompiler decompiler(
			Settings()
				.apiKey(argv[1])
		);
		auto decompilation = decompiler.runDecompilation(
			DecompilationArguments()
				.mode("bin")
				.inputFile(File::fromFilesystem(argv[2]))
		);
		decompilation->waitUntilFinished();
		//std::cout << decompilation->getOutputHll();
		fs << decompilation->getOutputHll();
		return 0;
	} catch (const Error &ex) {
		std::cerr << "error: " << ex.what() << "\n";
		return 1;
	}
}
