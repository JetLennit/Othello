#pragma once
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

struct position {
    int x;
    int y;
};

struct legal_play {
    position pos;
    bool directions[8] = {};
};

void moveDirection(position &pos, int direction);
bool outOfBounds(position pos); 

