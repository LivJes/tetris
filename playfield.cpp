//
// Created by liv on 15/12/18.
//

#include <iostream>
#include "playfield.hpp"

Playfield::Playfield(Dimensions dimensions)
    : dimensions_(dimensions)
    , field_() {
    initializeField();
}

Dimensions Playfield::getDimensions() const {
    return dimensions_;
}

std::array<std::array<Position, 12>, 10> Playfield::getField() {
    return field_;
}

bool Playfield::isGameOver() const {
        for (int i = 0; i < dimensions_.width_/50; ++i)
        {
            if (field_[i][0] == Position::Occupied) return true;
        }

        return false;
}

int Playfield::clearLine(unsigned long gametime) {
    int linescleared = 0;
    for (int j = 0; j < dimensions_.height_/50; ++j)
    {
        int i = 0;
        while (i < dimensions_.width_/50)
        {
            if (field_[i][j] == Position::Free) {
                break;
            }
            ++i;
        }

        if (i == dimensions_.width_/50) {
            for (int k = j; k > 0; --k)
            {
                for (i = 0; i < dimensions_.width_/50; ++i)
                {
                    field_[i][k] = field_[i][k-1];
                }
            }
            ++linescleared;
        }
    }
    return linescleared*50;

}

bool Playfield::checkBorder(const Tetromino& tetromino, int value) const {
    int tx = tetromino.getPosition().first;
    int mostleft = -1;
    int mostright = 0;
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            if (tetromino.isTetrominoBlock(x, y)) {
                if (x <= mostleft || mostleft == -1) {
                    mostleft = x;
                }
                if (x >= mostright) {
                    mostright = x;
                }
            }
        }
    }
    mostleft = mostleft*50+value;
    mostright = (mostright+1)*50+value;
    if (value > 0) {
        return (tx+mostright <= dimensions_.width_);
    }
    if (value < 0) {
        return (tx + mostleft >= 0);
    }
    return tx+mostright < dimensions_.width_ && tx + mostleft > 0;
}

bool Playfield::tryRotate(Tetromino tetromino) const {
    tetromino.rotate();
    return checkBorder(tetromino, 0);
}

bool Playfield::checkCollisions(const Tetromino& tetromino) const {
    std::pair<int,int> tpos_ = tetromino.getPosition();
    int bottomoftetronimo_ = 0;
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            if (tetromino.isTetrominoBlock(x, y)) {
                if (y > bottomoftetronimo_) {
                    bottomoftetronimo_ = y;
                }
                if (field_[tpos_.first/50 + x][tpos_.second/50 + y+1] == Position::Occupied) {
                    return true;
                }
            }
        }

    }

    bottomoftetronimo_ = (bottomoftetronimo_+1)*50 + tetromino.getPosition().second;
    return bottomoftetronimo_ >= getDimensions().height_;
}


void Playfield::storeTetromino(const Tetromino &tetromino) {
    std::pair<int,int> tpos_ = tetromino.getPosition();
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            if (tetromino.isTetrominoBlock(x, y)) {
                field_[tpos_.first/50 + x][tpos_.second/50 + y] = Position::Occupied;
                }
            }
        }
}

void Playfield::initializeField() {
    for (int i = 0; i < dimensions_.width_/50; ++i)
        for (int j = 0; j < dimensions_.height_/50; ++j)
            field_[i][j] = Position::Free;
}

