#ifndef GAME_H
#define GAME_H

#include "board.h"

const int SHOW_MOVES = true;

class Game {
    public:
        Board board;
        int turn = 2;
        bool update();
        void draw();
        void finish();
};

#endif
