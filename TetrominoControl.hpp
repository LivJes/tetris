//
// Created by liv on 15/12/18.
//

#ifndef TETRIS_SDL_EVENT_HPP
#define TETRIS_SDL_EVENT_HPP

#include "playfield.hpp"
#include <SDL_events.h>

class TetrominoControl {
private:
    Tetromino* tetromino_;
    Playfield playfield_;
public:
    explicit TetrominoControl(Tetromino* t, Playfield p)
        : tetromino_(t)
        , playfield_(p)
        {
            keyToEvent(input());
        }

    int input()
    {
        SDL_Event event;
        while ( SDL_PollEvent(&event) )
        {
            switch (event.type) {
                case SDL_KEYDOWN:
                    return event.key.keysym.sym;
                case SDL_QUIT:
                    exit(3);
                default:
                    break;
            }
        }
        return -1;
    }

    void keyToEvent(int input) {
        switch (input) {
            case SDLK_RIGHT:
                if (playfield_.checkBorder(*(tetromino_), 10) && !playfield_.checkCollisions(*(tetromino_))) {
                    tetromino_->move(10, 0);
                }
                break;
            case SDLK_LEFT:
                if (playfield_.checkBorder(*(tetromino_), -10) && !playfield_.checkCollisions(*(tetromino_))) {
                    tetromino_->move(-10, 0);
                }
                break;
            case SDLK_DOWN:
                tetromino_->move(0, 10);
                break;
            case SDLK_UP:
                if (playfield_.tryRotate(*(tetromino_))) {
                    tetromino_->rotate();
                }
                break;
            case SDLK_q:
                exit(0);
            default:
                break;
        }
    }
};

#endif //TETRIS_SDL_EVENT_HPP
