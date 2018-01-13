#include "command.h"

CommandParser::CommandParser(const std::string line)
{
	this->line = line;
	
	if (line.size() < 3) {
		this->name = "error";
		return;
	}

	if (line.substr(0, 3) == "add") {
		this->name = "add";

		try {
			int x = std::stoi(line.substr(4, 5));
			int y = std::stoi(line.substr(6, 7));
			int number = std::stoi(line.substr(8, 9));

			this->arguments = { x, y, number };
			return;
		}
		catch (std::exception) {
			this->name = "error";
			return;
		}
	}
	else if (line.substr(0, 3) == "rem") {
		this->name = "rem";

		try {
			int x = std::stoi(line.substr(4, 5));
			int y = std::stoi(line.substr(6, 7));

			this->arguments = { x, y };
			return;
		}
		catch (std::exception) {
			this->name = "error";
			return;
		}
	}
	else if (line.substr(0, 3) == "rdr") {
		this->name = "rdr";
		return;
	}
	else if (line.substr(0, 3) == "qit") {
		this->name = "qit";
		return;
	}
	else if (line.substr(0, 3) == "new") {
		this->name = "new";

		try {
			int c = std::stoi(line.substr(4, 5));

			this->arguments = { c };
			return;
		}
		catch (std::exception) {
			this->name = "error";
			return;
		}

		return;
	}
	else if (line.substr(0, 3) == "slv") {
		this->name = "slv";
	} else {
		this->name = "error";
	}
}

std::string CommandParser::getCommandName() {
	return this->name;
}

std::vector<int> CommandParser::getCommandArguments() {
	return this->arguments;
}
