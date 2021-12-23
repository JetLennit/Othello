#include <iostream>
#include <vector>
#include <string.h>
#include <SDL.h>
#include <game.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 660;

int textual() {
    std::cout << std::endl;
    Game game;
    while (true) {
        game.draw();
        if(!game.checkInput())
            break;
        game.update();
        break;
    }
    game.finish();
    game.draw();
    std::cout << "Game exited" << std::endl;

    return 0;
}

int graphical() {
    Game game;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    bool gameover = false;
    int mouse_x, mouse_y;
    while (!quit){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    if(game.checkInputSDL(mouse_x, mouse_y) && !game.over)
                        game.update();
                    break;
            }
        }

        game.drawSDL(renderer);
        SDL_RenderPresent(renderer);
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
              << "  -c <ip>  Connect to host at ip" << std::endl
              << "  -s       Host server          " << std::endl
              << "  -h, -?   Print this screen    " << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc == 1) 
        return graphical();

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
                case 'h':
                case '?':
                    help();
                    return 0;
                    break;
            }
        }
    }

    if (graphics)
        return graphical();
    else 
        return textual();

    return 0;
}

