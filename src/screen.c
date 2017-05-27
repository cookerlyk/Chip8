#include "screen.h"



// TODO: the double pointer and the dereference is a bit messy,
// try to refactor if possible or at least clean up
void init_window(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture) {
    (*window) = SDL_CreateWindow(
        "CHIP-8",                          // window label
        SDL_WINDOWPOS_CENTERED,            // initial x position
        SDL_WINDOWPOS_CENTERED,            // initial y position
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_OPENGL | 
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_ALLOW_HIGHDPI           // flags
    );

    // Check that the window was successfully created
    if ((*window) == NULL) {
        printf("Could not create SDL Window: %s\n", SDL_GetError());
        exit(1);
    }

    (*renderer) = SDL_CreateRenderer((*window), -1, 0);
    
    // Check that the renderer was successfully created
    if (*renderer == NULL) {
        printf("Could not create SDL Renderer: %s\n", SDL_GetError());
        exit(1);
    }

    (*texture) = SDL_CreateTexture((*renderer), 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT
    );

    // Check that the texture was successfully created
    if (*texture == NULL) {
        printf("Could not create SDL Texture: %s\n", SDL_GetError());
        exit(1);
    }
    
    // Set the screen to black initially
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
    SDL_RenderClear(*renderer);
    SDL_RenderPresent(*renderer);
}


void buffer_graphics(Chip8 *chip8, uint32_t *buffer, SDL_Renderer *renderer) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            uint8_t pixel = chip8->screen[y][x];
            buffer[(y * SCREEN_WIDTH) + x] = (0xFFFFFF00 * pixel) | 0x000000FF;
        }
    }
}


void draw_graphics(uint32_t *buffer, SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


void close_window(SDL_Window *window, SDL_Renderer* renderer, SDL_Texture *texture) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

