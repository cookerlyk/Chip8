#ifndef CHIP8_H
#define CHIP8_H

#include "instructions.h"


int load_rom(Chip8 *chip8, const char *rom_filename);
void init_system(Chip8 *chip8);
uint16_t fetch_opcode(Chip8 *chip8);
void execute_instruction(Chip8 *chip8);

void print_regs(Chip8 *chip8);


#endif // CHIP8_H
