#include "sudoku.h"
#include <algorithm>


Sudoku::Sudoku()
{
	createTable();
}

void Sudoku::newGame(size_t c_missingNumbers)
{
	createTable();

	std::mt19937 rng(rd());
	guessNumbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::shuffle(guessNumbers.begin(), guessNumbers.end(), rng);

	if (guessNumber(0, 0)) {
		for (size_t i = 0; i < c_missingNumbers; i++)
		{
			removeNumber(generateRandomNumber(), generateRandomNumber());
		}
	}
	else {
	}
}

int Sudoku::generateRandomNumber() {
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 8);
	return uni(rng);
}

bool Sudoku::guessNumber(int x, int y, int guess)
{
	// Did not find any solution to this cell.
	if (guess > 8) {
		table[x][y] = 0;
		return false;
	}

	// Find the next correct guess.
	while (!isCorrectNumber(x, y, guessNumbers[guess])) {
		guess += 1;

		if (guess > 8) {
			table[x][y] = 0;
			return false;
		}
	}

	table[x][y] = guessNumbers[guess];

	// The end of the sudoku table reached.
	if (x == 8 && y == 8) {
		return true;
	}

	// Go to the next cell. If it turns out no solution can be found with guess,
	// start again in this cell with guess + 1.
	if (!guessNumber(getNextColumn(x, y), getNextRow(x, y))) {
		return guessNumber(x, y, guess);
	}

	// Sudoku was completed.
	return true;
}



void Sudoku::addNumber(int x, int y, int number)
{
	table[x][y] = number;
}

void Sudoku::removeNumber(int x, int y) {
	table[x][y] = 0;
}

bool Sudoku::isCorrectNumber(int x, int y, int number) {
	std::vector<int> currentRow = getRow(y);
	std::vector<int> currentColumn = getColumn(x);
	std::vector<std::vector<int>> currentBlock = getBlock(x, y);

	if (std::find(currentRow.begin(), currentRow.end(), number) != currentRow.end()) {
		return false;
	}

	if (std::find(currentColumn.begin(), currentColumn.end(), number) != currentColumn.end()) {
		return false;
	}

	for (size_t x = 0; x < currentBlock.size(); x++)
	{
		if (std::find(currentBlock[x].begin(), currentBlock[x].end(), number) != currentBlock[x].end()) {
			return false;
		}
	}

	return true;
}

bool Sudoku::isCompleted()
{
	for (size_t x = 0; x < 9; x++)
	{
		for (size_t y = 0; y < 9; y++)
		{
			if (table[x][y] == 0 || !isCorrectNumber(x, y, table[x][y])) return false;
		}
	}

	return true;
}


#pragma region table accessories

void Sudoku::createTable() {
	// Reset current table.
	table.clear();

	// Create a new table consisting of columns and values 0.
	for (size_t x = 0; x < 9; x++)
	{
		std::vector<int> column;
		
		for (size_t y = 0; y < 9; y++)
		{
			column.push_back(0);
		}

		table.push_back(column);
	}
}

std::vector<int> Sudoku::getColumn(int x)
{
	return table[x];
}

std::vector<int> Sudoku::getRow(int y) {
	std::vector<int> row;

	for (size_t x = 0; x < 9; x++)
	{
		row.push_back(table[x][y]);
	}

	return row;
}

std::vector<std::vector<int>> Sudoku::getBlock(int x, int y) {
	size_t x0 = 3*(x / 3);
	size_t x1 = 3*(x / 3) + 3;
	size_t y0 = 3*(y / 3);
	size_t y1 = 3*(y / 3) + 3;

	std::vector<std::vector<int>> block;

	for (size_t x = x0; x < x1; x++)
	{
		std::vector<int> column;

		for (size_t y = y0; y < y1; y++)
		{
			column.push_back(table[x][y]);
		}

		block.push_back(column);
	}

	return block;
}

int Sudoku::getNextColumn(int x, int y) {
	if (x == 8) {
		return 0;
	}
	else {
		return x + 1;
	}
}

int Sudoku::getNextRow(int x, int y) {
	if (getNextColumn(x, y) == 0) {
		return y + 1;
	}

	return y;
}

std::ostream& operator<<(std::ostream& stream, Sudoku const &sudoku)
{
	stream << "+---+---+---+---+---+---+---+---+---+" << std::endl;

	for (size_t y = 0; y < 9; y++)
	{
		for (size_t x = 0; x < 9; x++)
		{
			if (sudoku.table[x][y] > 0) {
				stream << "| " << sudoku.table[x][y] << " ";
			}
			else {
				stream << "|   ";
			}
		}

		stream << "|" << std::endl;
		stream << "+---+---+---+---+---+---+---+---+---+" << std::endl;
	}

	return stream;
}

#pragma endregion
