#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "board.h"

const int X_OFFSET = 0;
const int Y_OFFSET = 20;
const int SCALE = 80;

const int SHOW_MOVES = false;

class Game {
    public:
        Board board;
        int turn = 2;
        bool over = false;
        bool checkInput();
        void update();
        void draw();
        bool checkInputSDL(int x, int y);
        void drawSDL(SDL_Renderer* renderer);
        void finish();
};

#endif
