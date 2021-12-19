#pragma once
#include "helper.h"

const int SHOW_MOVES = false;

class Game {
    public:
        int board[8][8] = {};
        std::vector<legal_play> legal_moves[2] = {};
        int turn = 1;
        Game();
        void refreshMoves();
        void addMove(int side, position pos, int direction); 
        legal_play getMove(int x, int y, int side);
        int hasMove(int x, int y);
        bool place(position pos);
        bool update();
        void draw();
};

