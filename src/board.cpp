#include <iostream>
#include <vector>
#include "board.h"

Board::Board() {
    tiles[3][3] = 1;
    tiles[4][4] = 1;
    tiles[3][4] = 2;
    tiles[4][3] = 2;

    refreshMoves();
}

void Board::refreshMoves() {
    legal_moves[0].clear();
    legal_moves[1].clear();

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (tiles[x][y]) 
                continue;

            int lx = 0;
            int ly = 0;

            for (int i = 0; i < 8; i++) {
                lx = x;
                ly = y;
                
                moveDirection(lx, ly, i);

                if (outOfBounds(lx, ly))
                    continue;

                int otherside = tiles[lx][ly];

                if(!otherside)  
                    continue;

                while (true) {
                    moveDirection(lx, ly, i);

                    if (outOfBounds(lx, ly)) 
                        break;

                    if (tiles[lx][ly] && tiles[lx][ly] != otherside) {
                        addMove(x, y, i, tiles[lx][ly]);
                        break; 
                    }
                } 
            }
        }
    }
}

void Board::addMove(int x, int y, int direction, int side) {
    if (legal_moves[side-1].empty()) {
        legal_play play;

        play.x = x;
        play.y = y;

        play.directions[direction] = true;
        legal_moves[side-1].push_back(play);
        return;
    }
    
    std::vector<legal_play>::iterator p;
    for (p = legal_moves[side-1].begin(); p != legal_moves[side-1].end(); ++p) {
        if (p->x == x && p->y == y) {
            p->directions[direction] = true;
            return;
        }
    }

    legal_play play;

    play.x = x;
    play.y = y;

    play.directions[direction] = true;
    legal_moves[side-1].push_back(play);
}

legal_play Board::getMove(int x, int y, int side) {
    legal_play play;

    std::vector<legal_play>::iterator p;
    for (p = legal_moves[side-1].begin(); p != legal_moves[side-1].end(); ++p) {
        if (p->x == x && p->y == y) {
            play = *p;
            break;
        }
    }

    return play;
}

int Board::checkMove(int x, int y) {
    int checked_move = 0;

    std::vector<legal_play>::iterator p;
    for (int i = 0; i <= 1; i++) {
        for (p = legal_moves[i].begin(); p != legal_moves[i].end(); ++p) {
            if (p->x == x && p->y == y) {
                checked_move += i+1;
            }
        }
    }
    return checked_move;
}

bool Board::place(int x, int y, int side) {
    if(outOfBounds(x, y))
        return false;
    
    int checked_move = checkMove(x, y);

    if(checked_move != side && checked_move != 3)
        return false;

    tiles[x][y] = side;

    legal_play play;

    play = getMove(x, y, side);

    int lx = x;
    int ly = y;

    for (int i = 0; i < 8; i++) {
        if (!play.directions[i])
            continue;

        int lx = x;
        int ly = y;

        while (true) {
            moveDirection(lx, ly, i);

            if (outOfBounds(lx, ly))
                break;

            if (tiles[lx][ly] == side || tiles[lx][ly] == 0)
                break;

            tiles[lx][ly] = side;
        }
    }

    return true;
}

int Board::getTile(int x, int y) {
    return tiles[x][y];
}

void Board::setTile(int x, int y, int side) {
    if (!outOfBounds(x, y))
        tiles[x][y] = side;
}

bool Board::hasMove(int side) {
    return !legal_moves[side-1].empty();
}

void Board::moveDirection(int &x, int &y, int direction){
    x += DIRECTIONS[direction][0];
    y += DIRECTIONS[direction][1];
}

bool Board::outOfBounds(int x, int y) {
    return (x < 0 || y < 0 || x >= 8 || y >= 8);
}
