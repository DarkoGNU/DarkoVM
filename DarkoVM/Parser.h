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
	// Memory segments
	enum class segment { S_ARGUMENT, S_LOCAL, S_STATIC, S_CONSTANT, S_THIS, S_THAT, S_POINTER, S_TEMP };

	// Constructor
	Parser();
	Parser(const std::filesystem::path path);

	// Handling commands
	bool hasMoreCommands();
	std::string advance();

	// Command types
	Parser::type commandType();
	Parser::operation calculationType();

	// Arguments
	std::string arg1();
	Parser::segment getSegment();
	int arg2();

	// File name
	std::string getFileName();

private:
	static std::unordered_map<std::string, Parser::type> commandMap;
	static std::unordered_map<std::string, Parser::operation> operationMap;
	static std::unordered_map<std::string, Parser::segment> segmentMap;
	void readFile();
	std::string cleanString(std::string text);
	std::string trimString(std::string text);
	void splitCommand();
};
