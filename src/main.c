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
    if (argv[2] != NULL && strcmp(argv[2], "log") == 0) {logging = TRUE;}

    Chip8 user_chip8;
    SDL_Window *chip8_screen;
    SDL_Renderer *chip8_renderer;
    SDL_Texture *chip8_texture;

    // Creates a buffer to store the pixel status for the emulator screen
    uint32_t *pixel_buffer = malloc(SCREEN_WIDTH * SCREEN_HEIGHT*sizeof(uint32_t));
    
    // Setup the window
    SDL_Init(SDL_INIT_VIDEO);
    init_window(&chip8_screen, &chip8_renderer, &chip8_texture);

    // Initilize the emulator into its startup state and load rom into memory
    init_system(&user_chip8);
    load_rom(&user_chip8, argv[1]);

    /* 
    * Main system loop begins here:
    * 1: Single instruction is executed
    * 2: Graphics are drawn to the screen (if draw flag set to true)
    * 3: User input is processed
    * 4: Timers are updated
    */
    while(user_chip8.is_running_flag){
        execute_instruction(&user_chip8, logging);

        // DEBUG: Register printout if logging
        if (logging) {print_regs(&user_chip8);}

        // If the draw screen flag was set to true during the last 
        // instruction, render the updated screen and then clear the flag
        if (user_chip8.draw_screen_flag) {
            buffer_graphics(&user_chip8, pixel_buffer, chip8_renderer);
            draw_graphics(pixel_buffer, chip8_renderer, chip8_texture);
            user_chip8.draw_screen_flag = FALSE;
        }
        
        // Store key input states and check for user exit command
        process_user_input(&user_chip8);
        update_timers(&user_chip8);
    }

    // Close and destroy the window (only called when the program is exited)
    close_window(chip8_screen, chip8_renderer, chip8_texture);
    free(pixel_buffer);

    return 0;
}
