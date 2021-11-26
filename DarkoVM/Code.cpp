#include "Code.h"

#include <format>

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
		handleAdd();
		break;
	case Parser::operation::O_SUB:
		handleSub();
		break;
	case Parser::operation::O_NEG:
		handleNeg();
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
		handleAnd();
		break;
	case Parser::operation::O_OR:
		handleOr();
		break;
	case Parser::operation::O_NOT:
		handleNot();
		break;
	}
}

void Code::handleAdd() {
	file << asmMap.getAsm("add");
}

void Code::handleSub() {
	file << asmMap.getAsm("sub");
}

void Code::handleNeg() {
	file << asmMap.getAsm("neg");
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

void Code::handleAnd() {
	file << asmMap.getAsm("and");
}

void Code::handleOr() {
	file << asmMap.getAsm("or");
}

void Code::handleNot() {
	file << asmMap.getAsm("not");
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
		writePushConstant();
		break;
	}
}

void Code::writePop() {
}

void Code::writePushConstant() {
	file << std::format(asmMap.getAsm("push_constant"), parser.arg2());
}

void Code::close() {
	file.close();
}
