#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include "Parser.h"
#include "AssemblyMap.h"

class Code {
	std::filesystem::path filePath;
	std::string fileName;
	std::ofstream file;

	Parser parser;
	AssemblyMap asmMap;

	int line;

public:
	// Constructor
	Code(std::filesystem::path path, AssemblyMap asmMap);

	// Set current parser
	void setParser(Parser newParser);

	// Translate and write the result
	void translate();

	// End the translation
	void close();

private:
	// Addin' & subtractin'
	void writeArithmetic();

	// Push'n'pop
	void writePushPop();
	void writePush();
	void writePop();
};
