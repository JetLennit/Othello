#ifndef GAME_H
#define GAME_H

#include "board.h"

const int SHOW_MOVES = true;

class Game {
    public:
        Board board;
        int turn = 2;
        bool checkInput();
        bool update();
        void draw();
        bool checkInputSDL(int x, int y);
        void drawSDL(SDL_Renderer* renderer);
        void finish();
};

#endif
