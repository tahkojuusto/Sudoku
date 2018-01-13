#pragma once

#include <vector>
#include <random>


class Sudoku {
public:
    Sudoku();
    
    friend std::ostream & operator<<(std::ostream& stream, Sudoku const &sudoku);
    
    void newGame(size_t missingNumbers = 0);
    void addNumber(int x, int y, int number);
    void removeNumber(int x, int y);
    bool isCorrectNumber(int x, int y, int number);
    bool isCompleted();
    
private:
    std::vector<std::vector<int>> table;
    
    std::random_device rd;
    std::vector<int> guessNumbers;
    
    void createTable();
    int generateRandomNumber();
    
    bool guessNumber(int x, int y, int guess = 0);
    
    std::vector<int> getColumn(int x);
    std::vector<int> getRow(int y);
    std::vector<std::vector<int>> getBlock(int x, int y);
    int getNextColumn(int x, int y);
    int getNextRow(int x, int y);
};
