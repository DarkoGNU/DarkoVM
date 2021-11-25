#include "Code.h"

Code::Code(std::filesystem::path path) {
	this->filePath = path;
}

void Code::setParser(Parser newParser) {
	this->parser = newParser;
	this->fileName = parser.getFileName();
}

void Code::translate() {
	while (parser.hasMoreCommands()) {
		parser.advance();

		if (parser.commandType() == Parser::type::C_ARITHMETIC) {
			this->writeArithmetic();
		}
		else {
			this->writePushPop();
		}
	}
}

void Code::writeArithmetic() {
}

void Code::writePushPop() {
	if (parser.commandType() == Parser::type::C_PUSH) {
		this->writePush();
	}
	else {
		this->writePop();
	}
}

void Code::writePush() {
	if
}

void Code::writePop() {
}
