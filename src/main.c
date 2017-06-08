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

#include <unistd.h>
#include <time.h>

#define CPU_CLOCK_DELAY 1000            // 1 millisecond
#define TIMER_CLOCK_DIVISION 9


int main (int argc, char *argv[]) {

    srand(time(NULL));  // seed the RNG
    int logging = FALSE;
    int timing = FALSE;

    if (argv[1] == NULL) {
        printf("Program Usage: ./chip8 path/to/rom\n");
        exit(EXIT_FAILURE);
    }

    // check the command line argv[2] to see if logging or debug timing is enabled
    if (argv[2] != NULL && strcmp(argv[2], "log") == 0) {logging = TRUE;}
    if (argv[2] != NULL && strcmp(argv[2], "time") == 0) {timing = TRUE;}

    Chip8 user_chip8;
    SDL_Window *chip8_screen;
    SDL_Renderer *chip8_renderer;
    SDL_Texture *chip8_texture;
    
    // Used to track the cycles for clock speed
    int division_cycles = 0;
    int total_cycles = 0;

    // Creates a buffer to store the pixel status for the emulator screen
    uint32_t *pixel_buffer = malloc((SCREEN_HEIGHT * SCREEN_WIDTH) * sizeof(uint32_t));
    
    // Setup the window
    SDL_Init(SDL_INIT_EVERYTHING);
    init_window(&chip8_screen, &chip8_renderer, &chip8_texture);

    // Initilize the emulator into its startup state and load rom into memory
    init_system(&user_chip8);
    load_rom(&user_chip8, argv[1]);

    /***************************************************************
    * Main system loop begins here:
    * 1: Single instruction is executed
    * 2: Graphics are drawn to the screen (if draw flag set to true)
    * 3: User input is processed
    * 4: Timers are updated
    ****************************************************************/
    time_t start = time(NULL);
    while(user_chip8.is_running_flag){
        execute_instruction(&user_chip8, logging);
        division_cycles++;
        total_cycles++;

        // DEBUG: Register printout if logging
        if (logging) {print_regs(&user_chip8);}

        // If the draw screen flag was set to true during the last 
        // instruction, render the updated screen and then clear the flag
        if (user_chip8.draw_screen_flag) {
            buffer_graphics(&user_chip8, pixel_buffer, chip8_renderer);
            draw_graphics(pixel_buffer, chip8_renderer, chip8_texture);
            user_chip8.draw_screen_flag = FALSE;
        }
        
        // Store key input states and check for user exit and pause commands.
        // If the user presses the spacebar to pause the emulation, the program will stay
        // in this loop until the user clears the is_paused_flag or presses the esc key
        do {
            process_user_input(&user_chip8);
        } while (user_chip8.is_paused_flag && user_chip8.is_running_flag);

        // Update the timers at a rate different from the CPU clock
        // Orginal spec was ~60hz vs the ~540hz for the Chip8 machine
        if (division_cycles == TIMER_CLOCK_DIVISION) {
            update_timers(&user_chip8);
            division_cycles = 0;
        }

        // slow down the emulation clock speed
        // TODO: Better way needed?
        usleep(CPU_CLOCK_DELAY);
    }
    
    // DEBUG: CPU cycle timing measurement
    if (timing) {
        double elapsed_time = (double)(time(NULL) - start);
        printf("Run time: %.2f\n", elapsed_time);
        printf("Cycles: %i\n", total_cycles);
        printf("Cycles Per Second: %i\n", (int)(total_cycles / elapsed_time));
    }
    
    // Close and destroy the window (only called when the program is exited)
    close_window(chip8_screen, chip8_renderer, chip8_texture);
    free(pixel_buffer);

    return 0;
}
