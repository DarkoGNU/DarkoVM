#include "AssemblyMap.h"

#include <fstream>
#include <filesystem>

bool AssemblyMap::initialize(std::string folder) {
	std::vector<std::filesystem::path> asmFiles;

	// Get all file names
	for (auto const& entry : std::filesystem::recursive_directory_iterator(folder)) {
		if (!entry.is_regular_file()) {
			continue;
		}

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
		dataMap[entry.filename().stem().string()] = content.str();

		if (file.bad()) {
			return false;
		}
	}

	return true;
}

std::string AssemblyMap::getAsm(std::string command) {
	return dataMap[command];
}
