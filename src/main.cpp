#include <SDL.h>
#include <cstring>
#include <iostream>
#include <vector>

#include "game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 660;

int textual(Game &game) {
    std::cout << std::endl;

    while (true) {
        game.draw();
        if(!game.checkInput())
            break;
        game.update();
    }
    game.finish();
    game.draw();
    std::cout << "Game exited" << std::endl;

    return 0;
}

int graphical(Game &game) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    int mouse_x = 0;
    int mouse_y = 0;
    while (!quit){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    if(game.checkInputSDL(mouse_x, mouse_y) && !game.isOver())
                        game.update();
                    else if (game.isOver())
                        game = Game();
                    break;
            }
        }

        game.drawSDL(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000/30);
    }  

    game.finish();
    SDL_DestroyWindow( window );

    SDL_Quit();

    return 0;
}

void help() {
    std::cout << "Usage:                          " << std::endl 
              << "  ./othello [options]           " << std::endl << std::endl 
              << "Options:                        " << std::endl
              << "  -t       Text mode            " << std::endl
              << "  -d       Disable move hints   " << std::endl
            //<< "  -c <ip>  Connect to host at ip" << std::endl
            //<< "  -s       Host server          " << std::endl
              << "  -h, -?   Print this screen    " << std::endl;
}

int main(int argc, char *argv[]) {
    Game game;

    if (argc == 1) 
        return graphical(game);

    bool graphics = true;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && strlen(argv[i]) != 1) {
            switch (argv[i][1]) {
                case 't':
                    graphics = false;
                    break;
                case 'c':
                    // for network code later
                    if (i + 1 < argc) 
                        std::cout << "Connecting to " << argv[i + 1] << std::endl;
                    else
                        std::cout << "Please add IP after -c" << std::endl;
                    break;
                case 's':
                    //for network code later
                    std::cout << "Hosting" << std::endl;
                    break;
                case 'd':
                    game.disableShowMoves();
                    break;
                case 'h':
                case '?':
                    help();
                    return 0;
                    break;
            }
        }
    }

    if (!graphics)
        return textual(game);

    return graphical(game);
}

