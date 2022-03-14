//
// Created by liv on 07/01/19.
//

#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include <SDL_image.h>
#include <iostream>
#include "playfield.hpp"


class GameEngine {
private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    SDL_Surface *img_;
    TTF_Font *font_;
    TTF_Font *gameover_;
public:
    enum color { BLACK, INTERFACE, ORANGE, CYAN, RED, YELLOW, MAGENTA, GREEN, AMBER, WHITE };

    GameEngine() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error("SDL Initialization fail");
        }
        TTF_Init();
        SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window_, &renderer_);
        img_ = IMG_Load("assets/tetris-logo.png");
        if (img_ == nullptr) {
            std::cerr << "Loading texture failed: " << IMG_GetError() << "\n";
        }
        font_ = TTF_OpenFont("assets/Oxygen-Bold.ttf", 24);
        gameover_ = TTF_OpenFont("assets/Oxygen-Bold.ttf", 80);
        if (font_ == nullptr || gameover_ == nullptr) {
           std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << "\n";
           throw std::runtime_error("Could not load font.");
        }
    }

    void renderGame(Playfield* playfield, Tetromino* tetromino) {
        rectangle(0, 0, 500, 600, false, GameEngine::color::INTERFACE);
        drawTetromino(tetromino);
        drawStoredTetrominos(playfield);
    }

    void renderInfo(Tetromino* nextetromino, int score, const std::string& best) {
        SDL_Texture *image = SDL_CreateTextureFromSurface(renderer_, img_);
        int imW = 0;
        int imH = 0;
        SDL_QueryTexture(image, nullptr, nullptr, &imW, &imH);
        SDL_Rect impos = { 550, 10, imW, imH };
        SDL_RenderCopy(renderer_, image, nullptr, &impos);

        std::string scorestring = "Score: " + std::to_string(score);
        const char *cstr = scorestring.c_str();

        SDL_Color color = { 255, 255, 255, 0 };
        SDL_Surface *surface = TTF_RenderText_Solid(font_, cstr, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
        setRenderColor(color::WHITE);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
        SDL_Rect txtpos = { 550, 300, texW, texH };
        SDL_RenderCopy(renderer_, texture, nullptr, &txtpos);

        std::string bestscorestring = "Best score: " + best;
        const char *cbestscore = bestscorestring.c_str();
        SDL_Surface *bestsurface = TTF_RenderText_Solid(font_, cbestscore, color);
        SDL_Texture *bestscore = SDL_CreateTextureFromSurface(renderer_, bestsurface);
        setRenderColor(color::WHITE);
        int bestW = 0;
        int bestH = 0;
        SDL_QueryTexture(bestscore, nullptr, nullptr, &bestW, &bestH);
        SDL_Rect bestpos = { 550, 400, bestW, bestH };
        SDL_RenderCopy(renderer_, bestscore, nullptr, &bestpos);


        nextetromino->showcase();
        drawTetromino(nextetromino);

        setRenderColor(color::BLACK);
        SDL_RenderPresent(renderer_);
        SDL_DestroyTexture(image);
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(bestscore);
        SDL_FreeSurface(surface);
        SDL_FreeSurface(bestsurface);
    }

    void renderGameOver() {
        SDL_Color color = { 255, 255, 255, 0 };
        SDL_Surface *surface = TTF_RenderText_Solid(gameover_, "Game Over", color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
        setRenderColor(color::WHITE);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
        SDL_Rect txtpos = { 200, 200, texW, texH };
        SDL_RenderCopy(renderer_, texture, nullptr, &txtpos);

        SDL_RenderPresent(renderer_);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }

    void setRenderColor(GameEngine::color color) {
        switch(color) {
            case color::BLACK:
                SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
                break;
            case color::INTERFACE:
                SDL_SetRenderDrawColor(renderer_, 0, 0, 225, 225);
                break;
            case color::ORANGE:
                SDL_SetRenderDrawColor(renderer_, 255, 128, 0, 0);
                break;
            case color::CYAN:
                SDL_SetRenderDrawColor(renderer_, 0, 255, 255, 0);
                break;
            case color::RED:
                SDL_SetRenderDrawColor(renderer_, 225, 0, 0, 0);
                break;
            case color::YELLOW:
                SDL_SetRenderDrawColor(renderer_, 225, 225, 0, 0);
                break;
            case color::MAGENTA:
                SDL_SetRenderDrawColor(renderer_, 225, 0, 225, 0);
                break;
            case color::GREEN:
                SDL_SetRenderDrawColor(renderer_, 0, 225, 0, 0);
                break;
            case color::AMBER:
                SDL_SetRenderDrawColor(renderer_, 255, 192, 0, 0);
                break;
            case color::WHITE:
                SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 0);
            default:
                SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
                break;
        }
    }

    void rectangle(int x1, int y1, int x2, int y2, bool filled, GameEngine::color color) {
        setRenderColor(color);
        SDL_Rect rect{x1, y1, x2, y2};
        if (filled) {
            SDL_RenderFillRect(renderer_, &rect);
        } else {
            SDL_RenderDrawRect(renderer_, &rect);
        }
    }

    void drawStoredTetrominos(Playfield *playfield) {
        Dimensions dimensions = playfield->getDimensions();
        std::array<std::array<Position, 12>, 10> field = playfield->getField();
        for (int i = 0; i < dimensions.width_ / 50; i++) {
            for (int j = 0; j < dimensions.height_ / 50; j++) {
                if (field[i][j] == Position::Occupied) {
                    rectangle(i * 50, j * 50, 49, 49, true, GameEngine::color::INTERFACE);
                }
            }
        }
    }

    void clear() {
        SDL_RenderClear(renderer_);
        setRenderColor(color::BLACK);
    }

    void drawTetromino(Tetromino *tetromino) {
        GameEngine::color color;
        switch (tetromino->getType()) {
            case Tetromino::I:
                color = GameEngine::color::ORANGE;
                break;
            case Tetromino::J:
                color = GameEngine::color::CYAN;
                break;
            case Tetromino::L:
                color = GameEngine::color::RED;
                break;
            case Tetromino::O:
                color = GameEngine::color::YELLOW;
                break;
            case Tetromino::S:
                color = GameEngine::color::MAGENTA;
                break;
            case Tetromino::T:
                color = GameEngine::color::GREEN;
                break;
            case Tetromino::Z:
                color = GameEngine::color::AMBER;
                break;
            default:
                color = GameEngine::color::INTERFACE;
                break;
        }
        auto position = tetromino->getPosition();
        for (auto x = 0; x < 5; ++x)
            for (auto y = 0; y < 5; ++y)
                if (tetromino->isTetrominoBlock(x, y) == 1) {
                    rectangle((position.first+x*50), (position.second+y*50), 49, 49, true, color);
                }
    }

    ~GameEngine() {
        SDL_FreeSurface(img_);
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        TTF_CloseFont(font_);
        TTF_CloseFont(gameover_);
        TTF_Quit();
        SDL_Quit();
    }
};

#endif //GAMEENGINE_HPP
