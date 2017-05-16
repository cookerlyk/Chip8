#include "chip8.h"


// Load the rom into memory
void load_rom(Chip8 *chip8, const char *rom_filename) {
    FILE *file = fopen(rom_filename, "rb");
    if (file != NULL) {
        // TODO: load rom into memory
        printf("%s\n", rom_filename);
    }
    else {
        // TODO: handle the error correctly
        printf("ERROR: File does not exist\n");
    }
}


/* 
* Initilize the system to its startup state, all of the 
* ram elements are set to 0, the stack is cleared, and the registers 
* are cleared. The PC register starts execution at location 0x200
* in memory
*/
void init_system(Chip8 *chip8) {
    chip8->pc_reg = 0x200;
    chip8->current_op = 0;
    chip8->sp_reg = 0;
    chip8->I_reg = 0;

    // TODO: Clear display

    // Clear stack
    for (int i = 0; i < STACK_SIZE; i++) {
        chip8->stack[i] = 0;
    }

    // Clear ram, calloc instead?
    for (int i = 0; i < TOTAL_RAM; i++) {
        chip8->ram[i] = 0;
    }

    // Clear registers
    for (int i = 0; i < NUM_V_REGISTERS; i++) {
        chip8->V[i] = 0;
    }

    // TODO: load fontset

    // TODO: reset timers
}
