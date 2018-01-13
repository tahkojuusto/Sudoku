#pragma once

#include <string>
#include <vector>

class CommandParser {
private:
	std::string name;
	std::vector<int> arguments;
	std::string line;

public:
	CommandParser(std::string line);

	std::string getCommandName();
	std::vector<int> getCommandArguments();
};
