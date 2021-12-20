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

            position origin;
            origin.x = x;
            origin.y = y;
            for (int i = 0; i < 8; i++) {
                position pos = origin;
                
                moveDirection(pos, i);

                if (outOfBounds(pos))
                    continue;

                int otherside = tiles[pos.x][pos.y];

                if(!otherside)  
                    continue;

                while (true) {
                    moveDirection(pos, i);

                    if (outOfBounds(pos)) 
                        break;

                    if (tiles[pos.x][pos.y] && tiles[pos.x][pos.y] != otherside) {
                        addMove(origin, i, tiles[pos.x][pos.y]);
                        break; 
                    }
                } 
            }
        }
    }
}

void Board::addMove(position pos, int direction, int side) {
    if (legal_moves[side-1].empty()) {
        legal_play play;
        play.pos = pos;
        play.directions[direction] = true;
        legal_moves[side-1].push_back(play);
    }

    else {
        std::vector<legal_play>::iterator p;
        for (p = legal_moves[side-1].begin(); p != legal_moves[side-1].end(); ++p) {
            if (p->pos.x == pos.x && p->pos.y == pos.y) {
                p->directions[direction] = true;
                return;
            }
        }
        legal_play play;
        play.pos = pos;
        play.directions[direction] = true;
        legal_moves[side-1].push_back(play);
    }
}

legal_play Board::getMove(int x, int y, int side) {
    legal_play play;

    std::vector<legal_play>::iterator p;
    for (p = legal_moves[side-1].begin(); p != legal_moves[side-1].end(); ++p) {
        if (p->pos.x == x && p->pos.y == y) {
            play = *p;
            break;
        }
    }

    return play;
}

int Board::checkMove(int x, int y) {
    std::vector<legal_play>::iterator p;

    int checked_move = 0;

    for (int i = 0; i <= 1; i++) {
        for (p = legal_moves[i].begin(); p != legal_moves[i].end(); ++p) {
            if (p->pos.x == x && p->pos.y == y) {
                checked_move += i+1;
            }
        }
    }
    return checked_move;
}

bool Board::place(position pos, int side) {
    if(outOfBounds(pos))
        return false;
    
    int checked_move = checkMove(pos.x, pos.y);

    if(checked_move != side && checked_move != 3)
        return false;

    tiles[pos.x][pos.y] = side;

    legal_play play;

    play = getMove(pos.x, pos.y, side);

    for (int i = 0; i < 8; i++) {
        if (!play.directions[i])
            continue;

        position movedpos = pos;

        while (true) {
            movedpos.x += DIRECTIONS[i][0]; 
            movedpos.y += DIRECTIONS[i][1]; 
            if (tiles[movedpos.x][movedpos.y] == side)
                break;

            tiles[movedpos.x][movedpos.y] = side;
        }
    }

    return true;
}

int Board::getTile(int x, int y) {
    return tiles[x][y];
}

bool Board::hasMove(int side) {
    return !legal_moves[side-1].empty();
}
