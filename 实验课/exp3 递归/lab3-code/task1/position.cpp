#include "position.h"
#include <cmath>  

// 构造函数实现
Position::Position(int r, int c) : row(r), col(c) {}

// 检查两个位置是否冲突的函数实现
bool Position::conflictsWith(const Position& other) const {
    // 行相同、列相同或在同一对角线
    return row == other.row || col == other.col ||
           (abs(row - other.row) == abs(col - other.col));
}

// 检查位置是否在棋盘范围内的函数实现（可选）
bool Position::isValid(int boardSize) const {
    return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
}
