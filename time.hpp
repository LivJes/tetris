//
// Created by liv on 08/01/19.
//

#ifndef TETRIS_TIME_HPP
#define TETRIS_TIME_HPP


#include <SDL_quit.h>
#include <SDL_timer.h>

static Uint32 next_time;

Uint32 timeLeft() {
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

#endif //TETRIS_TIME_HPP
