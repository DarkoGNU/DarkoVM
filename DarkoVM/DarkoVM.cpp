#include <iostream>
#include <string>
#include <filesystem>

#include "Parser.h"
#include "Code.h"

int main(int argc, char* argv[]) {
	// Initialize some variables
	std::string vmFile(argv[1]);

	std::filesystem::path vmPath(vmFile);
	std::filesystem::path asmPath;

	std::vector<std::filesystem::path> inFiles;

	// Handle directories
	if (!std::filesystem::exists(vmPath)) {
		std::cout << "Please specify a file/directory\n";
		return 0;
	}

	if (std::filesystem::is_directory(vmPath)) {
		for (auto const& entry : std::filesystem::recursive_directory_iterator(vmPath)) {
			inFiles.push_back(entry);
		}
	}
	else {
		inFiles.push_back(vmPath);
	}

	// Determine the out file's path
	if (std::filesystem::is_directory(vmPath)) {
		std::string asmFile = vmPath.filename().string().append(".asm");
	}
	else {
		inFiles.push_back(vmPath);
	}
}
