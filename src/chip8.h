#ifndef CHIP8_H
#define CHIP8_H

#include <stdio.h>
#include "instructions.h"


#define PC_START 0x200
#define TIMER_MAX 255


int load_rom(Chip8 *chip8, const char *rom_filename);
void init_system(Chip8 *chip8);
uint16_t fetch_opcode(Chip8 *chip8);
void execute_instruction(Chip8 *chip8);


#endif // CHIP8_H
