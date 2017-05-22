#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 1280

void init_window(SDL_Window *window);
void close_window(SDL_Window *window);

#endif // SCREEN_H
