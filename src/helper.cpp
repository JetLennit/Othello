#include "helper.h"

void moveDirection(int &x, int &y, int direction){
    x += DIRECTIONS[direction][0];
    y += DIRECTIONS[direction][1];
}

bool outOfBounds(int x, int y) {
    return (x < 0 || y < 0 || x >= 8 || y >= 8);
}
