#include "Code.h"

Code::Code(std::filesystem::path path) {
	this->filePath = path;
}

void Code::setParser(Parser newParser) {
	this->parser = newParser;
	this->fileName = parser.getFileName();
}

void Code::translate() {
}

void Code::writeArithmetic() {
}

void Code::writePushPop() {
}
