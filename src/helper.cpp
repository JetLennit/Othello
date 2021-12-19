#include "helper.h"

void moveDirection(position &pos, int direction){
    pos.x += DIRECTIONS[direction][0];
    pos.y += DIRECTIONS[direction][1];
}

bool outOfBounds(position pos) {
    return (pos.x < 0 || pos.y < 0 || pos.x == 8 || pos.y == 8);
}
