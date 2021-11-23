#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "Parser.h"
#include "Code.h"

int main(int argc, char* argv[]) {
	std::string vmFile(argv[1]);
	std::cout << "Translating " + vmFile + "...\n";

	std::filesystem::path vmPath(vmFile);

	Parser parser(vmPath);
}
