#include "chip8.h"


// Load the rom into memory
void load_rom(Chip8 *chip8, const char *rom_filename) {
    FILE *rom = fopen(rom_filename, "rb");
    if (rom != NULL) {
        printf("%s\n", rom_filename);

        // get the size of the rom to allocate memory for a buffer
        fseek(rom, 0, SEEK_END);
        long rom_length = ftell(rom); // TODO: does this need to be a long?
        rewind(rom);

        uint8_t *rom_buffer = (uint8_t*) malloc(sizeof(uint8_t) * rom_length);
        if (rom_buffer == NULL) {
            printf("ERROR: out of memory");
        }
        fread(rom_buffer, sizeof(uint8_t), (size_t)rom_length, rom); // TODO: handle error if not read into memory?

        //long buffer_size = rom_buffer.length();

        // TODO: rom size verfication? 0xfff - 0x200 >= rom_length
        for(int i = 0; i < rom_length; i++)
            chip8->ram[i + 0x200] = rom_buffer[i];
        }

    else {
        // TODO: handle the error correctly
        printf("ERROR: File does not exist\n");
    }

    fclose(rom);
    //free(rom_buffer); // FIXME: gives an undeclared error
}


/* 
* Initilize the system to its startup state, all of the 
* ram elements are set to 0, the stack is cleared, and the registers 
* are cleared. The PC register starts execution at location 0x200
* in memory
*/
void init_system(Chip8 *chip8) {
    chip8->pc_reg = PC_START;
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

    // Reset timers to their max values
    chip8->delay_timer = TIMER_MAX;
    chip8->sound_timer = TIMER_MAX;
}


uint16_t fetch_opcode(Chip8 *chip8) {
    // TODO: actually grab the next opcode from the memory
    return 0x1fff;
}


void execute_instruction(Chip8 *chip8) {
    uint16_t opcode = fetch_opcode(&chip8);
    chip8->current_op = opcode;

    switch(opcode) {

        // TODO: Cases calling the corresponding opcode functions

        default:
            printf("Unrecognized opcode: %x\n", opcode);
    }
}

