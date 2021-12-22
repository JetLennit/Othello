#include <iostream>
#include <vector>
#include "netlinux.h"
#include "game.h"

int main() {
    std::cout << std::endl;
    Server server;
    Game game;
    while (true) {
        game.draw();
        if(!game.update())
            break;
    }
    server.closeServer();
    game.finish();
    std::cout << "Game exited" << std::endl;
}
