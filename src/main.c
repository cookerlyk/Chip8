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
    SDL_Renderer *chip8_renderer;
    
    // Setup the window
    SDL_Init(SDL_INIT_VIDEO);
    init_window(&chip8_screen, &chip8_renderer);

    // Put the emulator into its startup state
    init_system(&user_chip8);

    // TODO: handle if the rom load fails?
    load_rom(&user_chip8, argv[1]);


    /* 
    * Main system loop begins here:
    * 1: Single instruction is executed
    * 2: Graphics are drawn to the screen
    * 3: User input is processed
    * 4: Timers are updated
    */
    // int color_shift = 0;
    while(user_chip8.is_running){
        execute_instruction(&user_chip8, logging);

        // Register printout if logging command line arg entered
        if (logging) {
            print_regs(&user_chip8);
        }
        
        // draw graphics TEST
        // printf("%i\n", color_shift);
        // if (color_shift == 500000) {
        //     render_graphics(chip8_renderer);
        //     break;
        // }
        // color_shift++;

        render_graphics(chip8_renderer);

        // Store key input states and check for user exit command
        process_user_input(&user_chip8);
        update_timers(&user_chip8);
    }

    // Close and destroy the window
    close_window(chip8_screen);

        
    return 0;
}


