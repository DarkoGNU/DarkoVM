#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>

class Parser {
	std::filesystem::path filePath;
	std::string fileName;

	int current;
	std::vector<std::string> commands;
	std::vector<std::string> currentCommand;

public:
	// Instruction types
	enum class type { C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL };
	// Arithmetic types
	enum class operation { O_ADD, O_SUB, O_NEG, O_EQ, O_GT, O_LT, O_AND, O_OR, O_NOT };

	// Constructor
	Parser();
	Parser(const std::filesystem::path path);

	// Handling commands
	bool hasMoreCommands();
	void advance();
	Parser::type commandType();
	Parser::operation calculationType();

	// Arguments
	std::string arg1();
	std::string arg2();

	// File name
	std::string getFileName();

private:
	static std::unordered_map<std::string, Parser::type> commandMap;
	static std::unordered_map<std::string, Parser::operation> operationMap;
	void readFile();
	std::string cleanString(std::string text);
	std::string trimString(std::string text);
	void splitCommand();
};
