#pragma once

#include <filesystem>
#include <string>

#include "Parser.h"

class Code {
	std::filesystem::path filePath;
	std::string fileName;
	Parser parser;

public:
	// Constructor
	Code(std::filesystem::path path);

	// Set current parser
	void setParser(Parser newParser);

	// Translate and write the result
	void translate();

private:
	void writeArithmetic();

	// Push'n'pop
	void writePushPop();
	void writePush();
	void writePop();
};
