#include "application.h"
#include <iostream>
#include <vector>

const int BOARD_SIZE = 8; // 棋盘大小为 8x8
std::vector<Position> queens; // 存储皇后位置的容器

void Application::initialize() {
    queens.clear();
}


Position Application::getStartPosition() {
    return Position(0, 0);
}


bool Application::isValid(const Position& p) {
    for (const auto& queen : queens) {
        if (p.conflictsWith(queen)) {
            return false; // 存在冲突，返回 false
        }
    }
    return true; // 没有冲突，可以放置
}


void Application::progress(const Position& p) {
    queens.push_back(p);
}

bool Application::success(const Position& p) {
    return queens.size() == BOARD_SIZE;
}


void Application::goBack(const Position& p) {
    if (!queens.empty()) {
        queens.pop_back();
    }
}


void Application::print() {
    for (const auto& queen : queens) {
        std::cout << "Queen at (" << queen.row << ", " << queen.col << ")\n";
    }
    std::cout << "--------------------\n";
}


Application::Iterator::Iterator() : currItrPosPtr(nullptr) {}


Application::Iterator::Iterator(const Position& currP) : currItrPosPtr(new Position(currP)) {}


Application::Iterator::~Iterator() {
    delete static_cast<Position*>(currItrPosPtr);
}


Position Application::Iterator::getNextPosition() {
    Position* currPos = static_cast<Position*>(currItrPosPtr);
    if (currPos->col + 1 < BOARD_SIZE) {
        return Position(currPos->row, currPos->col + 1); // 同一行的下一个列
    } else {
        return Position(currPos->row + 1, 0); // 移到下一行的第一个列
    }
}


bool Application::Iterator::noNextPosition() {
    Position* currPos = static_cast<Position*>(currItrPosPtr);
    return currPos->row >= BOARD_SIZE || currPos->col >= BOARD_SIZE;
}
