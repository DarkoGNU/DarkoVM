#pragma once

#include <filesystem>
#include <string>
#include <vector>

class Parser {
	std::filesystem::path filePath;
	std::string fileName;

	int current;
	std::vector<std::string> commands;

public:
	// Instruction types
	enum class type { C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL };

	// Constructor
	Parser(std::filesystem::path path);

	// Handling commands
	bool hasMoreCommands();
	void advance();

	// Arguments
	std::string arg1();
	std::string arg2();

private:
	void readFile();
	std::string cleanString(std::string text);
	std::string trimString(std::string text);
};
