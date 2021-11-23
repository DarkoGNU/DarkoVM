#include <iostream>
#include <string>
#include <filesystem>

#include "Parser.h"
#include "Code.h"

int main(int argc, char* argv[]) {
	std::string vmFile(argv[1]);
	std::filesystem::path vmPath(vmFile);
	std::vector<std::filesystem::path> outFiles;

	if (!std::filesystem::exists(vmPath)) {
		std::cout << "Please specify a file/directory\n";
		return 0;
	}

	if (std::filesystem::is_directory(vmPath)) {
		for (auto const& entry : std::filesystem::recursive_directory_iterator(vmPath)) {
			outFiles.push_back(entry);
		}
	}
	else {
		outFiles.push_back(vmPath);
	}



}
