#include "screen.h"



// TODO: the double pointer and the dereference is a bit messy,
// try to refactor if possible or at least clean up
void init_window(SDL_Window **window, SDL_Renderer **renderer) {
    (*window) = SDL_CreateWindow(
        "CHIP8",                           // window label
        SDL_WINDOWPOS_CENTERED,            // initial x position
        SDL_WINDOWPOS_CENTERED,            // initial y position
        WINDOW_WIDTH,                      // width
        WINDOW_HEIGHT,                     // height
        SDL_WINDOW_OPENGL                  // flags
    );

    // Check that the window was successfully created
    if ((*window) == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    (*renderer) = SDL_CreateRenderer((*window), -1, 0);
    
    // Check that the renderer was successfully created
    if (*renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    
    // Set the screen to black initially
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);
}


void render_graphics(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}


void close_window(SDL_Window *window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

