#include <iostream>
#include <retdec/retdec.h>

using namespace retdec;

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " API-KEY FILE\n";
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
        std::cout << decompilation->getOutputHll();
        return 0;
    } catch (const Error &ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}