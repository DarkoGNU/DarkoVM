#pragma once

#include <filesystem>
#include <string>

class Code {
public:
	// Constructor
	Code(std::filesystem::path path);

	// Currently translated file's name
	void setFileName(std::string name);

	// Translate and write an arithmetic command
	void writeArithmetic(std::string command);

	// Translate and write a push/pop command
	void writePushPop(std::string command);

	// Close the output file
	void close();
};
