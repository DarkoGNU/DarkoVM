#pragma once

#include <filesystem>
#include <string>

class Parser {
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
};
