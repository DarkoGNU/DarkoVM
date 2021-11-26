#include "Code.h"

#include <format>
#include <iostream> // temp

Code::Code(std::filesystem::path path, AssemblyMap asmMap) {
	this->filePath = path;
	file = std::ofstream(path);

	this->asmMap = asmMap;

	line = -1;
}

void Code::setParser(Parser newParser) {
	this->parser = newParser;
	this->fileName = parser.getFileName();
}

void Code::translate() {
	// Provide code to write constants

	while (parser.hasMoreCommands()) {
		std::string instruction = parser.advance();
		file << "// " << instruction << ", line " << ++line << "\n";

		if (parser.commandType() == Parser::type::C_ARITHMETIC) {
			this->writeArithmetic();
		}
		else {
			this->writePushPop();
		}
	}

	if (file.bad()) {
		throw std::runtime_error("I/O Error");
	}
}

void Code::writeArithmetic() {
	switch (parser.calculationType()) {
	case Parser::operation::O_ADD:
		file << asmMap.getAsm("add");
		break;
	case Parser::operation::O_SUB:
		file << asmMap.getAsm("sub");
		break;
	case Parser::operation::O_NEG:
		file << asmMap.getAsm("neg");
		break;
	case Parser::operation::O_EQ:
		handleEq();
		break;
	case Parser::operation::O_GT:
		handleGt();
		break;
	case Parser::operation::O_LT:
		handleLt();
		break;
	case Parser::operation::O_AND:
		file << asmMap.getAsm("and");
		break;
	case Parser::operation::O_OR:
		file << asmMap.getAsm("or");
		break;
	case Parser::operation::O_NOT:
		file << asmMap.getAsm("not");
		break;
	}
}

void Code::handleEq() {
	std::string notEqual = "NOTEQUAL" + std::to_string(line);
	std::string equal = "EQUAL" + std::to_string(line);
	std::string end = "END" + std::to_string(line);

	file << std::format(asmMap.getAsm("eq"), notEqual, equal, end);
}

void Code::handleGt() {
	std::string notGreater = "NOTGREATER" + std::to_string(line);
	std::string greater = "GREATER" + std::to_string(line);
	std::string end = "END" + std::to_string(line);

	file << std::format(asmMap.getAsm("gt"), notGreater, greater, end);
}

void Code::handleLt() {
	std::string notSmaller = "NOTSMALLER" + std::to_string(line);
	std::string smaller = "SMALLER" + std::to_string(line);
	std::string end = "END" + std::to_string(line);

	file << std::format(asmMap.getAsm("lt"), notSmaller, smaller, end);
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
	Parser::segment seg = parser.getSegment();

	switch (seg) {
	case Parser::segment::S_CONSTANT:
		file << std::format(asmMap.getAsm("push_constant"), parser.arg2());
		break;
	case Parser::segment::S_LOCAL:
		file << std::format(asmMap.getAsm("push_local"), parser.arg2());
		break;
	case Parser::segment::S_ARGUMENT:
		file << std::format(asmMap.getAsm("push_argument"), parser.arg2());
		break;
	case Parser::segment::S_THIS:
		file << std::format(asmMap.getAsm("push_this"), parser.arg2());
		break;
	case Parser::segment::S_THAT:
		file << std::format(asmMap.getAsm("push_that"), parser.arg2());
		break;
	}
}

void Code::writePop() {
	Parser::segment seg = parser.getSegment();

	switch (seg) {
	case Parser::segment::S_LOCAL:
		file << std::format(asmMap.getAsm("pop_local"), parser.arg2());
		break;
	case Parser::segment::S_ARGUMENT:
		file << std::format(asmMap.getAsm("pop_argument"), parser.arg2());
		break;
	case Parser::segment::S_THIS:
		file << std::format(asmMap.getAsm("pop_this"), parser.arg2());
		break;
	case Parser::segment::S_THAT:
		file << std::format(asmMap.getAsm("pop_that"), parser.arg2());
		break;
	}
}

void Code::close() {
	file.close();
}
