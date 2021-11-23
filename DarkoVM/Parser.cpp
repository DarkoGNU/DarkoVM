#include "Parser.h"

#include <fstream>
#include <regex>
#include <iostream> // debugging

Parser::Parser(std::filesystem::path path) {
	this->filePath = path;
	this->fileName = filePath.filename().string();
	current = -1;
	this->commands;

	size_t index = fileName.find_last_of('.');
	fileName = fileName.substr(0, index);

	this->readFile();
}

bool Parser::hasMoreCommands() {
	return false;
}

void Parser::advance() {
}

std::string Parser::arg1() {
	return std::string();
}

std::string Parser::arg2() {
	return std::string();
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
