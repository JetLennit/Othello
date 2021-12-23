#ifndef BOARD_H
#define BOARD_H

const int DIRECTIONS[8][2] = {
    {-1, -1},
    { 0, -1},
    { 1, -1},
    {-1,  0},
    { 1,  0},
    {-1,  1},
    { 0,  1},
    { 1,  1}
};

struct legal_play {
    int x = 0;
    int y = 0;
    bool directions[8] = {};
};

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
        void setTile(int x, int y, int side);
        void moveDirection(int &x, int &y, int direction);
        bool outOfBounds(int x, int y); 

    private:
        int tiles[8][8] = {};
        std::vector<legal_play> legal_moves[2] = {};
};

#endif
