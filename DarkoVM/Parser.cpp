#include "Parser.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <iostream> // debugging

Parser::Parser(std::filesystem::path path) {
	this->filePath = path;
	this->fileName = filePath.filename().string();
	current = -1;
	this->commands;
	this->currentCommand.reserve(3);

	size_t index = fileName.find_last_of('.');
	fileName = fileName.substr(0, index);

	this->readFile();
}

bool Parser::hasMoreCommands() {
	return (current + 1) < commands.size();
}

void Parser::advance() {
	current++;
	splitCommand();
}

Parser::type Parser::commandType() {
	std::string command = currentCommand.at(0);

	if (commandMap.contains(command)) {
		return commandMap[command];
	}

	return Parser::type::C_ARITHMETIC;
}

std::string Parser::arg1() {
	return currentCommand.at(1);
}

std::string Parser::arg2() {
	return currentCommand.at(2);
}

void Parser::readFile() {
	std::ifstream textFile(filePath);

	if (textFile.bad()) {
		return;
	}

	std::string line;
	while (std::getline(textFile, line)) {
		line = cleanString(line);

		if (line.empty()) {
			continue;
		}

		commands.push_back(line);
		std::cout << line << "\n";
	}
}

std::string Parser::cleanString(std::string text) {
	// find and erase comments
	size_t comment = text.find("//");
	if (comment != std::string::npos) {
		text.erase(comment);
	}

	// remove unnecessary whitespace
	return trimString(text);
}

std::string Parser::trimString(std::string text) {
	// remove leading and trailing spaces
	std::regex pattern(R"(^\s+|\s+$)");
	text = std::regex_replace(text, pattern, "");

	// remove double spaces
	pattern = R"(\s+)";
	return std::regex_replace(text, pattern, " ");
}

void Parser::splitCommand() {
	std::string command = commands.at(current);

	std::stringstream split(command);
	std::string item;

	for (int i = 0; i < 3; i++) {
		if (std::getline(split, item, ' ')) {
			currentCommand.at(i) = item;
		}
		else {
			currentCommand.at(i) = std::string();
		}
	}
}

std::unordered_map<std::string, Parser::type> Parser::commandMap = {
	// if the command isn't found, we'll return C_ARITHMETIC
	{"push", Parser::type::C_PUSH},
	{"pop", Parser::type::C_POP},

	{"label", Parser::type::C_LABEL},
	{"goto", Parser::type::C_GOTO},
	{"if-goto", Parser::type::C_IF},

	{"function", Parser::type::C_FUNCTION},
	{"call", Parser::type::C_CALL},
	{"return", Parser::type::C_RETURN}
};
