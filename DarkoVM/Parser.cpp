#include "Parser.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

Parser::Parser(const std::filesystem::path path) {
	this->filePath = path;
	this->fileName = filePath.filename().stem().string();
	current = -1;

	std::size_t index = fileName.find_last_of('.');
	fileName = fileName.substr(0, index);

	this->readFile();
}

// Default constructor
Parser::Parser() {}

bool Parser::hasMoreCommands() {
	return (current + 1) < commands.size();
}

std::string Parser::advance() {
	current++;
	splitCommand();
	return commands.at(current);
}

Parser::type Parser::commandType() {
	std::string command = currentCommand.at(0);

	if (commandMap.contains(command)) {
		return commandMap[command];
	}

	return Parser::type::C_ARITHMETIC;
}

Parser::operation Parser::calculationType() {
	return operationMap[currentCommand.at(0)];
}

std::string Parser::arg1() {
	if (this->commandType() == Parser::type::C_ARITHMETIC) {
		return currentCommand.at(0);
	}

	return currentCommand.at(1);
}

Parser::segment Parser::getSegment() {
	return segmentMap[currentCommand.at(1)];
}

int Parser::arg2() {
	return std::stoi(currentCommand.at(2));
}

std::string Parser::getFileName() {
	return fileName;
}

void Parser::readFile() {
	std::ifstream textFile(filePath);
	std::string line;

	while (std::getline(textFile, line)) {
		if (textFile.bad()) {
			throw std::runtime_error("I/O Error");
			return;
		}

		line = cleanString(line);

		if (line.empty()) {
			continue;
		}

		commands.push_back(line);
	}
}

std::string Parser::cleanString(std::string text) {
	// find and erase comments
	std::size_t comment = text.find("//");
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
	currentCommand.clear();

	std::stringstream split(command);
	std::string item;

	for (int i = 0; i < 3; i++) {
		if (std::getline(split, item, ' ')) {
			currentCommand.push_back(item);
		}
		else {
			currentCommand.push_back(std::string());
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

std::unordered_map<std::string, Parser::operation> Parser::operationMap = {
	{"add", Parser::operation::O_ADD},
	{"sub", Parser::operation::O_SUB},
	{"neg", Parser::operation::O_NEG},
	{"eq", Parser::operation::O_EQ},
	{"gt", Parser::operation::O_GT},
	{"lt", Parser::operation::O_LT},
	{"and", Parser::operation::O_AND},
	{"or", Parser::operation::O_OR},
	{"not", Parser::operation::O_NOT}
};

std::unordered_map<std::string, Parser::segment> Parser::segmentMap = {
	{"argument", Parser::segment::S_ARGUMENT},
	{"local", Parser::segment::S_LOCAL},
	{"static", Parser::segment::S_STATIC},
	{"constant", Parser::segment::S_CONSTANT},
	{"this", Parser::segment::S_THAT},
	{"pointer", Parser::segment::S_POINTER},
	{"temp", Parser::segment::S_TEMP}
};
