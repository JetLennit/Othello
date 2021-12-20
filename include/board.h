#pragma once
#include "helper.h"

class Board {
    public:
        Board();
        void refreshMoves();
        void addMove(int x, int y, int direction, int side); 
        legal_play getMove(int x, int y, int side);
        int checkMove(int x, int y);
        bool hasMove(int side);
        bool place(int x, int y, int side);
        int getTile(int x, int y);

    private:
        int tiles[8][8] = {};
        std::vector<legal_play> legal_moves[2] = {};
};
