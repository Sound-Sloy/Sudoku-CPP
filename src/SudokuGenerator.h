#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


class SudokuGenerator {
private:
    std::vector<std::vector<int32_t>> board;
    std::vector<std::vector<int32_t>> board_full;
    std::random_device rd;
    std::mt19937 gen{ rd() };
public:
    SudokuGenerator();
    void Generate();
    bool Solve(int32_t row, int32_t col);
    bool IsValid(int32_t row, int32_t col, int32_t num);
    void PrintBoard();
    std::vector<int32_t> GetBoard();
    std::vector<std::vector<int32_t>> GetBoard_2D();
    std::vector<int32_t> GetFullBoard();
    std::vector<std::vector<int32_t>> GetFullBoard_2D();
    int32_t GetCell(int32_t ID);
};