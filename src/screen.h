#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "chip8_t.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 1280

void init_window(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **sdl_texture);
void buffer_graphics(Chip8 *chip8, uint32_t *buffer, SDL_Renderer *renderer);
void draw_graphics(uint32_t *buffer, SDL_Renderer *renderer, SDL_Texture *texture);
void close_window(SDL_Window *window, SDL_Renderer* renderer, SDL_Texture *texture);

#endif // SCREEN_H
