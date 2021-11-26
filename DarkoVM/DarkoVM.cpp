#include <iostream>
#include <string>
#include <filesystem>

#include "Parser.h"
#include "Code.h"
#include "AssemblyMap.h"

int main(int argc, char* argv[]) {
	// Initialize some variables
	std::string vmFile(argv[1]);
	std::filesystem::path vmPath(vmFile);

	std::string asmFile;
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
		asmFile = vmPath.filename().string().append(".asm");
	}
	else {
		asmFile = vmPath.stem().string().append(".asm");
	}

	// Initialize the AssemblyMap
	AssemblyMap asmMap;

	if (asmMap.initialize("Data")) {
		std::cout << "AssemblyMap initialized successfully...\n\n";
	}
	else {
		std::cout << "AssemblyMap couldn't initialize\n";
		return 0;
	}

	// Initialize the Code writer
	asmPath = std::filesystem::path(asmFile);
	Code codeWriter(asmPath, asmMap);

	// Translate all input files
	for (auto const& entry : inFiles) {
		std::cout << "Translating " << entry.string() << "...\n";

		Parser parser(entry);
		codeWriter.setParser(parser);
		codeWriter.translate();
	}

	std::cout << "\nTranslation complete!\n";
}
