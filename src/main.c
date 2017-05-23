/*  
* Chip8 Interpreter
*
* The interpreter takes one argument when ran from the command line, 
* the name and path of the rom the user wants to run on the system. 
*
* Example startup input: <unix> ./chip8 rom_dir/rom_name
* 
* To enable command line logging: <unix> ./chip8 rom_dir/rom_name log
*/

#include <string.h>
#include "chip8.h"
#include "screen.h"


int main (int argc, char *argv[]) {
    srand(time(NULL));  // seed the RNG
    int logging = FALSE;

    // check the command line argv[2] to see if logging is enabled
    if (argv[2] != NULL && strcmp(argv[2], "log") == 0) {
        logging = TRUE;
    }

    Chip8 user_chip8;
    SDL_Window *chip8_screen;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);

    chip8_screen = SDL_CreateWindow(
        "CHIP8",                           // window label
        SDL_WINDOWPOS_CENTERED,            // initial x position
        SDL_WINDOWPOS_CENTERED,            // initial y position
        WINDOW_WIDTH,                      // width
        WINDOW_HEIGHT,                     // height
        SDL_WINDOW_OPENGL                  // flags
    );

    /**********************************************
    * test initial drawing code
    ***********************************************/
    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(chip8_screen, -1, 0);
    // Place a black background to start
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    // This will show the new contents of the window.
    SDL_RenderPresent(renderer);
    /**********************************************
    * end test initial drawing code
    ***********************************************/



    // TODO: setup input
    init_system(&user_chip8);

    // TODO: handle if the rom load fails
    load_rom(&user_chip8, argv[1]);

    // System loop
    uint8_t color_shift = 0;
    while(user_chip8.is_running){
        execute_instruction(&user_chip8);

        // Register printout if logging command line arg entered
        if (logging) {
            print_regs(&user_chip8);
        }
        
        // draw graphics
        SDL_SetRenderDrawColor(renderer, 0, color_shift, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        if (color_shift == 255) {
            color_shift = 0;
        }
        color_shift++;
        
        // Store key input states and check for user exit command
        process_user_input(&user_chip8);
    }

    // Close and destroy the window
    close_window(chip8_screen);

        
    return 0;
}


