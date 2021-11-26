#pragma once

#include <string>
#include <unordered_map>

class AssemblyMap {
	std::unordered_map<std::string, std::string> dataMap;

public:
	bool initialize(std::string folder);
	std::string getAsm(std::string command);
};
