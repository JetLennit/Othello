#pragma once
#include "helper.h"
#include "board.h"

const int SHOW_MOVES = false;

class Game {
    public:
        Board board;
        int turn = 1;
        bool update();
        void draw();
};

