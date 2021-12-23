#include <iostream>
#include <vector>
#include <SDL.h>
#include <math.h>
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

bool Game::checkInputSDL(int x, int y) {
    double relative_mouse_x = (x-X_OFFSET)/80;
    double relative_mouse_y = (y-Y_OFFSET)/80;

    return board.place(floor(relative_mouse_x), floor(relative_mouse_y), turn);
}

void Game::update() {
    turn = (!(turn-1)) + 1;

    board.refreshMoves();

    if (!board.hasMove(1) && !board.hasMove(2)) 
        finish();
    else if (!board.hasMove(turn))
        update();
}

void Game::drawSDL(SDL_Renderer* renderer) {
    //SDL_SetRenderDrawColor(renderer, 5, 25, 20, 10);
    SDL_SetRenderDrawColor(renderer, 10, 50, 40, 255);
    SDL_RenderClear(renderer);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            SDL_Rect square = {x*SCALE+5+X_OFFSET, y*SCALE+5+Y_OFFSET, SCALE-10, SCALE-10};
            switch (board.getTile(x, y)) {
                case 1:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &square);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &square);
                    break;
                case 0:
                    int checked = board.checkMove(x, y);
                    if ((checked == turn || checked == 3) && SHOW_MOVES) {
                        SDL_SetRenderDrawColor(renderer, 27, 135, 108, 255);
                        SDL_RenderFillRect(renderer, &square);
                        SDL_Rect minisquare = {x*SCALE+20+X_OFFSET, y*SCALE+20+Y_OFFSET, SCALE-40, SCALE-40};
                        if (turn == 1)
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        else
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &minisquare);
                    }
                    else {
                        //SDL_SetRenderDrawColor(renderer, 10, 50, 40, 255);
                        SDL_SetRenderDrawColor(renderer, 27, 135, 108, 255);
                        SDL_RenderFillRect(renderer, &square);
                    }
                    break;
            }
        }
    }
    if (turn == 1)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    else if (turn == 2)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    if (turn) {
        SDL_Rect turnbar = {0, 0, 640, Y_OFFSET};
        SDL_RenderFillRect(renderer, &turnbar);
    }
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

    int winner = 0;
    if (white_points > black_points) 
        winner = 1;
    else if (black_points > white_points) 
        winner = 2;
    
    turn = winner;

    for (int y = 0; y < 8; y++) 
        for (int x = 0; x < 8; x++) 
            board.setTile(x, y, winner);

    over = true;
}
