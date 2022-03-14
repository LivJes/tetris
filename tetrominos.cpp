//
// Created by liv on 15/12/18.
//

#include "tetrominos.hpp"

Tetromino::Tetromino(TetroType type)
        : type_(type)
        , x_(200)
        , y_(-100)
        ,angle_(1) {}

Tetromino::TetroType Tetromino::getType() {
    return type_;
}

int Tetromino::isTetrominoBlock(int x, int y) const {
    return tetrominos_[type_][angle_][x][y];
}

void Tetromino::move(int x, int y) {
    x_ += x;
    y_ += y;
}

void Tetromino::rotate() {
    switch(angle_) {
        case 0:
            angle_ = 1;
            break;
        case 1:
            angle_ = 2;
            break;
        case 2:
            angle_ = 3;
            break;
        case 3:
            angle_ = 0;
            break;
        default:
            break;
    }
}

std::pair<int, int> Tetromino::getPosition() const {
    return {x_, y_};
}

void Tetromino::showcase() {
    x_ = 510;
    y_ = 75;
}