#include <iostream>
#include <vector>
#include "game.h"

bool Game::update() {

    std::string input;

    bool turn_over = false;
    
    while(!turn_over && board.hasMove(turn)) {
        std::cout << "Please enter coordinates (xy): ";
        std::cin >> input;

        while(input.length() < 2) 
            return false;

        int x = input.at(0)-'a';
        int y = input.at(1)-'0';

        turn_over = board.place(x, y, turn);
    }

    turn = (!(turn-1)) + 1;

    board.refreshMoves();

    return true;
}

void Game::draw() {
    std::string turn_name = (turn == 1) ? "White" : "Black";
    std::cout << "   " << turn_name << "'s turn!" << std::endl;

    std::cout << "  a b c d e f g h" << std::endl;
    for (int y = 0; y < 8; y++) {
        std::cout << y << '|';
        for (int x = 0; x < 8; x++) {
            switch (board.getTile(x, y)) {
                case 1:
                    std::cout << 'W';
                    break;
                case 2:
                    std::cout << 'B';
                    break;
                case 0:
                    if (board.checkMove(x, y) == turn && SHOW_MOVES) std::cout << '*';
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
