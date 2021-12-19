#include <iostream>

const int directions[8][2] = {
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

void moveDirection(position &pos, int direction){
    pos.x += directions[direction][0];
    pos.y += directions[direction][1];
}

bool outOfBounds(position pos) {
    return (pos.x < 0 || pos.y < 0 || pos.x == 8 || pos.y == 8);
}

class Game {
    public:
        int board[8][8] = {};
        int moves[8][8] = {};
        int turn = 1;
        Game();
        void update();
        void draw();
        void getMoves();
        bool place(position);
};

Game::Game() {
    // place initial pieces
    board[3][3] = 1;
    board[4][4] = 1;
    board[3][4] = 2;
    board[4][3] = 2;
}

void Game::getMoves() {
    for (int y = 0; y < 8; y++) 
        for (int x = 0; x < 8; x++) 
            moves[x][y] = 0;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y]) 
                continue;

            for (int i = 0; i < 8; i++) {
                position pos;
                pos.x = x;
                pos.y = y;
                
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
                        moves[x][y] += board[pos.x][pos.y];
                        break; 
                    }
                } 
            }
        }
    }
}

bool Game::place(position pos) {
    if(outOfBounds(pos))
        return false;

    if(moves[pos.x][pos.y] != turn)
        return false;

    board[pos.x][pos.y] = turn;

    for (int i = 0; i < 8; i++) {
        position p;
        p = pos; 

        while (true) {
            moveDirection(pos, i);

            if (outOfBounds(pos)) break;
            if (board[pos.x][pos.y]) {
                if (board[pos.x][pos.y] == turn) 
                    break; 

                board[p.x][p.y] = turn;
            }
        } 
    }

    return true;
}

void Game::update() {
    std::string input;

    bool turn_over = false;
    
    while(!turn_over) {
        std::cout << "Please enter the X and Y you want to place" << std::endl;
        std::cout << "For example: a8, c2, h4" << std::endl;
        std::cin >> input;

        while(input.length() != 2) {
            std::cout << "Error, please try again" << std::endl;
            std::cin >> input;
        }

        position pos;
        pos.x = input.at(0)-'a';
        pos.y = input.at(1)-'0';

        std::cout << pos.x << ' ' << pos.y << std::endl;

        turn_over = place(pos);
    }


    if (turn == 1) turn = 2;
    else turn = 1;
}

void Game::draw() {

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
                    if (moves[x][y]) std::cout << moves[x][y]+2;
                    else std::cout << ' ';
                    break;
            }
            std::cout << '|';
        }
        std::cout << y;
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

int main() {
    Game game;
    while (true) {
        game.getMoves();
        game.draw();
        game.update();
    }
}
