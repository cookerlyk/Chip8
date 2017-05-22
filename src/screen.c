#include "screen.h"


void init_window(SDL_Window *window) {
    window = SDL_CreateWindow(
        "CHIP8",                           // window label
        SDL_WINDOWPOS_CENTERED,            // initial x position
        SDL_WINDOWPOS_CENTERED,            // initial y position
        WINDOW_WIDTH,                      // width
        WINDOW_HEIGHT,                     // height
        SDL_WINDOW_OPENGL                  // flags
    );

    // Check that the window was successfully created
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }
}

void close_window(SDL_Window *window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

