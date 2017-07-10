#ifndef CHIP8_H
#define CHIP8_H

#include "instructions.h"
#include <SDL2/SDL.h>


// Keymap for the emulator. Comments are the orignal
// key on the hex keypad
const static uint8_t KEYMAP[NUM_KEYS] = {
    SDLK_x, // 0
    SDLK_1, // 1
    SDLK_2, // 2
    SDLK_3, // 3
    SDLK_q, // 4
    SDLK_w, // 5
    SDLK_e, // 6
    SDLK_a, // 7
    SDLK_s, // 8
    SDLK_d, // 9
    SDLK_z, // A
    SDLK_c, // B
    SDLK_4, // C
    SDLK_r, // D
    SDLK_f, // E
    SDLK_v  // F
};


void load_rom(Chip8 *chip8, const char *rom_filename);
void init_system(Chip8 *chip8);
void reset_system(Chip8 *chip8);
uint16_t fetch_opcode(Chip8 *chip8);
void execute_instruction(Chip8 *chip8, int logging);
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);

// Debugging functions
void print_regs(Chip8 *chip8);
void print_stack(Chip8 *chip8);
void print_keyboard(Chip8 *chip8);


#endif // CHIP8_H
