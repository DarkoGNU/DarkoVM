#include "AssemblyMap.h"

#include <fstream>
#include <filesystem>

bool AssemblyMap::initialize(std::string folder) {
	std::vector<std::filesystem::path> asmFiles;

	for (auto const& entry : std::filesystem::recursive_directory_iterator(folder)) {
		asmFiles.push_back(entry);
	}

	if (asmFiles.empty()) {
		return false;
	}

	// Map all .asm files
	for (auto const& entry : asmFiles) {
		std::ifstream file(entry);
		std::stringstream content;

		content << file.rdbuf();
		dataMap[entry.filename().stem().string()] =  content.str();
	}
}