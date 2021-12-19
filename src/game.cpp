#include <iostream>
#include <vector>
#include "game.h"

Game::Game() {
    // place initial pieces
    board[3][3] = 1;
    board[4][4] = 1;
    board[3][4] = 2;
    board[4][3] = 2;
}

void Game::refreshMoves() {
    legal_moves[0].clear();
    legal_moves[1].clear();

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y]) 
                continue;

            position origin;
            origin.x = x;
            origin.y = y;
            for (int i = 0; i < 8; i++) {
                position pos = origin;
                
                moveDirection(pos, i);

                if (outOfBounds(pos))
                    continue;

                int otherside = board[pos.x][pos.y];

                if(!otherside)  
                    continue;

                while (true) {
                    moveDirection(pos, i);

                    if (outOfBounds(pos)) 
                        break;

                    if (board[pos.x][pos.y] && board[pos.x][pos.y] != otherside) {
                        addMove(board[pos.x][pos.y], origin, i);
                        break; 
                    }
                } 
            }
        }
    }
}

void Game::addMove(int side, position pos, int direction) {
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

legal_play Game::getMove(int x, int y, int side) {
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

int Game::hasMove(int x, int y) {
    std::vector<legal_play>::iterator p;

    int has_move = 0;

    for (int i = 0; i <= 1; i++) {
        for (p = legal_moves[i].begin(); p != legal_moves[i].end(); ++p) {
            if (p->pos.x == x && p->pos.y == y) {
                has_move += i+1;
            }
        }
    }
    return has_move;
}

bool Game::place(position pos) {
    if(outOfBounds(pos))
        return false;
    
    int has_move = hasMove(pos.x, pos.y);

    if(has_move != turn && has_move != 3)
        return false;

    board[pos.x][pos.y] = turn;

    legal_play play;

    play = getMove(pos.x, pos.y, turn);

    for (int i = 0; i < 8; i++) {
        if (!play.directions[i])
            continue;

        position movedpos = pos;

        while (true) {
            movedpos.x += DIRECTIONS[i][0]; 
            movedpos.y += DIRECTIONS[i][1]; 
            if (board[movedpos.x][movedpos.y] == turn)
                break;

            board[movedpos.x][movedpos.y] = turn;
        }
    }

    return true;
}

bool Game::update() {
    std::string input;

    bool turn_over = false;
    
    while(!turn_over && !legal_moves[turn].empty()) {
        std::cout << "Please enter coordinates (xy): ";
        std::cin >> input;

        while(input.length() < 2) 
            return false;

        position pos;
        pos.x = input.at(0)-'a';
        pos.y = input.at(1)-'0';

        turn_over = place(pos);
    }

    turn = (!(turn-1)) + 1;

    return true;
}

void Game::draw() {
    std::string turn_name = (turn == 1) ? "White" : "Black";

    std::cout << "   " << turn_name << "'s turn!" << std::endl;

    std::cout << "  a b c d e f g h" << std::endl;
    for (int y = 0; y < 8; y++) {
        std::cout << y << '|';
        for (int x = 0; x < 8; x++) {
            switch (board[x][y]) {
                case 1:
                    std::cout << 'W';
                    break;
                case 2:
                    std::cout << 'B';
                    break;
                case 0:
                    if (hasMove(x, y) == turn && SHOW_MOVES) std::cout << '*';
                    else std::cout << ' ';
                    break;
            }
            std::cout << '|';
        }
        std::cout << y;
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl << std::endl;
}
