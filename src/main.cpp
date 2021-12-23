#include <iostream>
#include <vector>
#include <SDL.h>
#include <game.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 660;

int main() {
    Game game;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow( "Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) {
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

