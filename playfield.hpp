//
// Created by liv on 15/12/18.
//

#ifndef TETRIS_PLAYFIELD_HPP
#define TETRIS_PLAYFIELD_HPP

#include <cstdlib>
#include <vector>
#include <array>
#include "tetrominos.hpp"

struct Dimensions {
    int width_;
    int height_;
};

enum class Position {
    Free,
    Occupied
};

class Playfield {
public:
    explicit Playfield(Dimensions dimensions);

    Dimensions getDimensions() const;

    std::array<std::array<Position, 12>, 10> getField();

    bool isGameOver() const;

    int clearLine(unsigned long gametime);

    bool checkBorder(const Tetromino& tetromino, int value) const;

    bool tryRotate(Tetromino tetromino) const;

    bool checkCollisions(const Tetromino& tetromino) const;

    void storeTetromino(const Tetromino& tetromino);

    ~Playfield() = default;

private:
    Dimensions dimensions_;
    std::array<std::array<Position, 12>, 10> field_;

    void initializeField();
};

#endif //TETRIS_PLAYFIELD_HPP
