#include <iostream>
#include <vector>
#include "helper.h"
#include "game.h"

int main() {
    std::cout << std::endl;
    Game game;
    while (true) {
        game.getMoves();
        game.draw();
        if(!game.update())
            break;
    }
}
