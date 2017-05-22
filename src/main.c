/*  
* Chip8 Interpreter
*
* The interpreter takes one argument when ran from the command line, 
* the name and path of the rom the user wants to run on the system. 
*
* Example startup input: <unix> ./chip8 rom_dir/rom_name
*/


#include "chip8.h"
#include "screen.h"


int main (int argc, char *argv[]) {

    srand(time(NULL));  // seed the RNG

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


    // TODO: setup input
    init_system(&user_chip8);

    // TODO: handle if the rom load fails
    load_rom(&user_chip8, argv[1]);

    // System loop
    uint8_t color_shift = 0;
    while(TRUE){
        execute_instruction(&user_chip8);

        // Test register printout 
        print_regs(&user_chip8);

        // draw graphics
        SDL_SetRenderDrawColor(renderer, 0, color_shift, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        if (color_shift == 255) {
            color_shift = 0;
        }
        color_shift++;
        
        // key input state stored
    }

    SDL_Delay(5000);  // Pause execution for 3000 milliseconds, for example


    // Close and destroy the window
    close_window(chip8_screen);

        
    return 0;
}


