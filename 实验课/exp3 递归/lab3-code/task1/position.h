#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    int row;  
    int col;  

    Position(int r = 0, int c = 0);// 构造函数

  
    bool conflictsWith(const Position& other) const;//检查位置冲突写在position里

    bool isValid(int boardSize) const;// 检查是否在棋盘里
};

#endif // POSITION_H
