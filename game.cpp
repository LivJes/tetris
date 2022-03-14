//
// Created by liv on 07/01/19.
//

#include <fstream>
#include "gameEngine.hpp"
#include "TetrominoControl.hpp"


int main() {

    GameEngine engine;
    bool gameRunning = true;
    bool gameEnded = false;
    unsigned long gametime = SDL_GetTicks();
    int score = 0;
    std::ifstream inscorefile("score.txt");
    std::string bestscore;
    if (inscorefile.good()) {
        bestscore = {std::istreambuf_iterator<char>(inscorefile), std::istreambuf_iterator<char>()};
        inscorefile.close();
    }

    Dimensions dimensions = {500, 600};

    Playfield playfield(dimensions);
    Tetromino tetromino{static_cast<Tetromino::TetroType>(random() % 7)};
    Tetromino nexttetromino{static_cast<Tetromino::TetroType>(random() % 7)};

    while(gameRunning) {
        TetrominoControl control(&tetromino, playfield);
        engine.renderGame(&playfield, &tetromino);
        engine.renderInfo(&nexttetromino, score, bestscore);
        if (SDL_GetTicks() > gametime) {
            gametime += 500;
            tetromino.move(0, 10);
        }
        if (playfield.checkCollisions(tetromino)) {
            playfield.storeTetromino(tetromino);
            tetromino = nexttetromino.getType();
            nexttetromino = static_cast<Tetromino::TetroType>(random() % 7);
        }
        score += playfield.clearLine(gametime);
        if (playfield.isGameOver()) {
            gameRunning = false;
            gameEnded = true;
        }
        engine.clear();
    }

    while(gameEnded) {
        TetrominoControl control(&tetromino, playfield);
        engine.renderGameOver();
        if (score > std::stoi(bestscore)) {
            std::ofstream scorefile("score.txt");
            if (scorefile.good()) {
                scorefile << score;
                scorefile.close();
            }
        }
    }

    return 0;
}