#include "Parser.h"

Parser::Parser(std::filesystem::path path) {
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
