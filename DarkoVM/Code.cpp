#include "Code.h"

Code::Code(std::filesystem::path path) {
	this->filePath = path;
	file = std::ofstream(path);
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
	file << "@" << "SP" << "\n"; // acquire the first address, decrement the stack pointer
	file << "AM=M-1" << "\n";

	file << "D=M" << "\n"; // acquire the first variable

	file << "@" << "SP" << "\n"; // acquire the second address
	file << "A=M-1" << "\n";
	file << "M=M+D" << "\n"; // add
}

void Code::handleSub() {
	file << "@" << "SP" << "\n"; // acquire the first address, decrement the stack pointer
	file << "AM=M-1" << "\n";

	file << "D=M" << "\n"; // acquire the first variable

	file << "@" << "SP" << "\n"; // acquire the second address
	file << "A=M-1" << "\n";

	file << "M=M-D" << "\n"; // subtract
}

void Code::handleNeg() {
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n";
	file << "M=-M" << "\n"; // negate its value
}

void Code::handleEq() {
	std::string notEqual = "NOTEQUAL" + std::to_string(line);
	std::string equal = "EQUAL" + std::to_string(line);
	std::string end = "END" + std::to_string(line);

	file << "@" << "SP" << "\n"; // acquire the first address, decrement the stack pointer
	file << "AM=M-1" << "\n";

	file << "D=M" << "\n"; // acquire the first variable

	file << "@" << "SP" << "\n"; // acquire the second address
	file << "A=M-1" << "\n";

	file << "D=M-D" << "\n"; // compute their value

	file << "@" << notEqual << "\n";
	file << "D;JNE" << "\n"; // jump if they're not equal
	file << "@" << equal << "\n";
	file << "0;JMP" << "\n"; // else, jump to another line

	file << "(" << notEqual << ")" << "\n"; // not equal
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n"; // correct it
	file << "M=0" << "\n"; // write false
	file << "@" << end << "\n"; // jump to the end
	file << "0;JMP" << "\n";

	file << "(" << equal << ")" << "\n"; // equal
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n"; // correct it
	file << "M=-1" << "\n"; // write true
	file << "@" << end << "\n"; // jump to the end
	file << "0;JMP" << "\n";

	// the end
	file << "(" << end << ")" << "\n";
}

void Code::handleGt() {
	std::string notGreater = "NOTGREATER" + std::to_string(line);
	std::string greater = "GREATER" + std::to_string(line);
	std::string end = "END" + std::to_string(line);

	file << "@" << "SP" << "\n"; // acquire the first address, decrement the stack pointer
	file << "AM=M-1" << "\n";

	file << "D=M" << "\n"; // acquire the first variable

	file << "@" << "SP" << "\n"; // acquire the second address
	file << "A=M-1" << "\n";

	file << "D=M-D" << "\n"; // compute their value

	file << "@" << notGreater << "\n";
	file << "D;JLE" << "\n"; // jump if it's not greater
	file << "@" << greater << "\n";
	file << "0;JMP" << "\n"; // else, jump to another line

	file << "(" << notGreater << ")" << "\n"; // not greater
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n"; // correct it
	file << "M=0" << "\n"; // write false
	file << "@" << end << "\n"; // jump to the end
	file << "0;JMP" << "\n";

	file << "(" << greater << ")" << "\n"; // greater
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n"; // correct it
	file << "M=-1" << "\n"; // write true
	file << "@" << end << "\n"; // jump to the end
	file << "0;JMP" << "\n";

	// the end
	file << "(" << end << ")" << "\n";
}

void Code::handleLt() {
	std::string notSmaller = "NOTSMALLER" + std::to_string(line);
	std::string smaller = "SMALLER" + std::to_string(line);
	std::string end = "END" + std::to_string(line);

	file << "@" << "SP" << "\n"; // acquire the first address, decrement the stack pointer
	file << "AM=M-1" << "\n";

	file << "D=M" << "\n"; // acquire the first variable

	file << "@" << "SP" << "\n"; // acquire the second address
	file << "A=M-1" << "\n";

	file << "D=M-D" << "\n"; // compute their value

	file << "@" << notSmaller << "\n";
	file << "D;JGE" << "\n"; // jump if it's not smaller
	file << "@" << smaller << "\n";
	file << "0;JMP" << "\n"; // else, jump to another line

	file << "(" << notSmaller << ")" << "\n"; // not greater
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n"; // correct it
	file << "M=0" << "\n"; // write false
	file << "@" << end << "\n"; // jump to the end
	file << "0;JMP" << "\n";

	file << "(" << smaller << ")" << "\n"; // greater
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n"; // correct it
	file << "M=-1" << "\n"; // write true
	file << "@" << end << "\n"; // jump to the end
	file << "0;JMP" << "\n";

	// the end
	file << "(" << end << ")" << "\n";
}

void Code::handleAnd() {
	file << "@" << "SP" << "\n"; // acquire the first address, decrement the stack pointer
	file << "AM=M-1" << "\n";

	file << "D=M" << "\n"; // acquire the first variable

	file << "@" << "SP" << "\n"; // acquire the second address
	file << "A=M-1" << "\n";
	file << "M=D&M" << "\n"; // and
}

void Code::handleOr() {
	file << "@" << "SP" << "\n"; // acquire the first address, decrement the stack pointer
	file << "AM=M-1" << "\n";

	file << "D=M" << "\n"; // acquire the first variable

	file << "@" << "SP" << "\n"; // acquire the second address
	file << "A=M-1" << "\n";
	file << "M=D|M" << "\n"; // or
}

void Code::handleNot() {
	file << "@" << "SP" << "\n"; // acquire the address
	file << "A=M-1" << "\n";
	file << "M=!M" << "\n"; // not
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
	file << "@" << parser.arg2() << "\n"; // acquire the constant
	file << "D=A" << "\n";

	file << "@" << "SP" << "\n"; // acquire the address, increment the stack pointer, 
	file << "AM=M+1" << "\n";
	file << "A=A-1" << "\n"; // correct the address

	file << "M=D" << "\n"; // push the constant
}

void Code::close() {
	file.close();
}
