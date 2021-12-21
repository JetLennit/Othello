#include <iostream>
#include <vector>
#include "game.h"

bool Game::checkInput() {
    std::string input;

    while (true) {
        std::cout << "Please enter coordinates \"xy\": ";
        std::cin >> input;

        if (input.length() != 2) {
            if (input.at(0) == '?')
                std::cout << "Enter x as a letter and y as a number or enter q to quit." << std::endl;
            else if (input.at(0) == 'q')
                return false;
            else
                std::cout << "Invalid response. Enter x as a letter and y as a number." << std::endl;
            continue;
        }

        int x = input.at(0)-'a';
        int y = input.at(1)-'0';

        if (board.outOfBounds(x, y)) {
            std::cout << "Invalid response. Enter x as a letter and y as a number." << std::endl;
            continue;
        }

        if (board.place(x, y, turn))
            break;

        std::cout << "Move not possible." << std::endl;
    }

    return true;
}

bool Game::update() {
    if (!board.hasMove(1) && !board.hasMove(2)) 
        return false;

    bool has_quit = !checkInput();

    turn = (!(turn-1)) + 1;

    board.refreshMoves();

    return !has_quit;
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

void Game::finish() {
    int white_points = 0;
    int black_points = 0;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            switch (board.getTile(x, y)) {
                case 1:
                    white_points++;
                    break;
                case 2:
                    black_points++;
                    break;
                case 0:
                    break;
            }
        }
    }

    if (white_points > black_points) 
        std::cout << "White wins!" << std::endl;
    else if (black_points > white_points) 
        std::cout << "Black wins!" << std::endl;
    else
        std::cout << "Draw!" << std::endl;
}
