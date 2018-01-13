#include "sudoku.h"
#include <iostream>
#include <string>
#include <exception>
#include "command.h"

int main() {
	Sudoku sudoku;
	
	std::cout << "Welcome to play sudoku!" << std::endl << std::endl;
	std::cout << "Create new game with x missing numbers: 'new x'." << std::endl;
	std::cout << "Add new number n to a cell (x, y) where x and y = 0,1,2,3,4,5,6,7,8: 'add x y n'." << std::endl;
	std::cout << "Remove existing number from a cell (x, y): 'rem x y'." << std::endl;
	std::cout << "Display the current table: 'rdr'." << std::endl;
	std::cout << "Exit the program: 'qit'." << std::endl;

	sudoku.newGame(50);
	std::cout << sudoku << std::endl;

	do {
		std::string command;
		std::getline(std::cin, command);

		CommandParser parser(command);
		std::string name = parser.getCommandName();
		std::vector<int> arguments = parser.getCommandArguments();

		if (name == "add") {
			if (sudoku.isCorrectNumber(arguments[0], arguments[1], arguments[2])) {
				sudoku.addNumber(arguments[0], arguments[1], arguments[2]);
			} else {
				std::cout << "invalid number." << std::endl;
			}
		} else if (name == "rem") {
			sudoku.removeNumber(arguments[0], arguments[1]);
		} else if (name == "rdr") {
			std::cout << sudoku << std::endl;
		} else if (name == "qit") {
			break;
		} else if (name == "new") {
			sudoku.newGame(arguments[0]);
			std::cout << "new game was created." << std::endl;
		} else {

		}
	} while (true);

	return 0;
}
