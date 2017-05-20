/*  
* Chip8 Interpreter
*
* The interpreter takes one argument when ran from the command line, 
* the name and path of the rom the user wants to run on the system. 
*
* Example startup input: <unix> ./chip8 rom_dir/rom_name
*/


#include "chip8.h"


int main (int argc, char *argv[]) {

    // seed the RNG
    srand(time(NULL));

    Chip8 user_chip8; // TODO: needs a better name

    // TODO: setup graphics
    // TODO: setup input

    init_system(&user_chip8);

    // TODO: handle if the rom load fails
    load_rom(&user_chip8, argv[1]);

    // System loop
    while(TRUE){
        execute_instruction(&user_chip8);

        // Test register printout 
        print_regs(&user_chip8);

        // draw graphics
        // key input state stored
    }
        
    return 0;
}


