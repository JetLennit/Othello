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

void moveDirection(position &pos, int direction){
    pos.x += DIRECTIONS[direction][0];
    pos.y += DIRECTIONS[direction][1];
}

bool outOfBounds(position pos) {
    return (pos.x < 0 || pos.y < 0 || pos.x == 8 || pos.y == 8);
}
