#ifndef HELPER_H
#define HELPER_H

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

void moveDirection(int &x, int &y, int direction);
bool outOfBounds(int x, int y); 

#endif
