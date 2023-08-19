#include "SudokuGenerator.h"

SudokuGenerator::SudokuGenerator() {
    board.resize(9, std::vector<int32_t>(9, 0));
}

void SudokuGenerator::Generate() {
    // Clear the board
    for (int32_t i = 0; i < 9; i++)
        for (int32_t j = 0; j < 9; j++)
            board[i][j] = 0;

    // Fill the diagonal boxes with random numbers
    for (int32_t i = 0; i < 9; i += 3) {
        std::vector<int32_t> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        shuffle(nums.begin(), nums.end(), gen);

        for (int32_t j = 0; j < 3; j++) {
            for (int32_t k = 0; k < 3; k++) {
                board[i + j][i + k] = nums[j * 3 + k];
            }
        }
    }

    // Solve the puzzle starting from the top-left corner
    if (!Solve(0, 0)) {
        std::cout << "Error: Failed to solve the puzzle" << std::endl;
        return;
    }

    this->board_full = board;
    // Remove random cells until the desired difficulty is reached
    int32_t numRemoved = 0;
    std::uniform_int_distribution<> dis(0, 8);

    while (numRemoved < 30) {
        int32_t row = dis(gen);
        int32_t col = dis(gen);

        if (board[row][col] != 0) {
            board[row][col] = 0;
            numRemoved++;
        }
    }
}

bool SudokuGenerator::Solve(int32_t row, int32_t col) {
    // If we've reached the end of the board, return true
    if (row == 9) {
        return true;
    }

    // If the current cell is already filled, move to the next cell
    if (board[row][col] != 0) {
        if (col == 8) {
            return Solve(row + 1, 0);
        }
        else {
            return Solve(row, col + 1);
        }
    }

    // Try filling the current cell with each possible number
    for (int32_t i = 1; i <= 9; i++) {
        if (IsValid(row, col, i)) {
            board[row][col] = i;

            if (col == 8) {
                if (Solve(row + 1, 0)) {
                    return true;
                }
            }
            else {
                if (Solve(row, col + 1)) {
                    return true;
                }
            }

            board[row][col] = 0;
        }
    }

    // If no number works, backtrack
    return false;
}

bool SudokuGenerator::IsValid(int32_t row, int32_t col, int32_t num) {
    // Check row
    for (int32_t i = 0; i < 9; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Check column
    for (int32_t i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 box
    int32_t boxRow = row - row % 3;
    int32_t boxCol = col - col % 3;

    for (int32_t i = 0; i < 3; i++) {
        for (int32_t j = 0; j < 3; j++) {
            if (board[boxRow + i][boxCol + j] == num) {
                return false;
            }
        }
    }

    // If the number is valid in all directions, return true
    return true;
}

void SudokuGenerator::PrintBoard() {
    for (int32_t i = 0; i < 9; i++) {
        for (int32_t j = 0; j < 9; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int32_t> SudokuGenerator::GetBoard() {
    std::vector<int32_t> res;
    res.resize(81);
    for (int32_t i = 0; i < 9; ++i)
        for (int32_t j = 0; j < 9; ++j)
            res[i * 9 + j] = this->board[i][j];
    return res;
}

std::vector<std::vector<int32_t>> SudokuGenerator::GetBoard_2D() {
    return this->board;
}

std::vector<int32_t> SudokuGenerator::GetFullBoard() {
    std::vector<int32_t> res;
    res.resize(81);
    for (int32_t i = 0; i < 9; ++i)
        for (int32_t j = 0; j < 9; ++j)
            res[i * 9 + j] = board_full[i][j];
    return res;
}

std::vector<std::vector<int32_t>> SudokuGenerator::GetFullBoard_2D() {
    return this->board_full;
}

int32_t SudokuGenerator::GetCell(int32_t ID) {
    return this->board[ID / 9][ID % 9];
}