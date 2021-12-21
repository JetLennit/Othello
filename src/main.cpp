#include <iostream>
#include <vector>
#include "game.h"

int main() {
    std::cout << std::endl;
    Game game;
    while (true) {
        game.draw();
        if(!game.update())
            break;
    }
    game.finish();
    std::cout << "Game exited" << std::endl;
}
