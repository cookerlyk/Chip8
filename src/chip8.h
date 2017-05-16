#ifndef CHIP8_H
#define CHIP8_H


#include <stdio.h>

#include "instructions.h"

typedef struct chip8 Chip8;

// FIXME: would like to use constants but circular imports happen, fix later
#define NUM_V_REGISTERS 16
#define TOTAL_RAM 4096
#define STACK_SIZE 16


struct chip8 {
    uint8_t ram[TOTAL_RAM];          // 4k of memory

    // registers 
    uint8_t V[NUM_V_REGISTERS];      // general purpose registers (0 - 14) and the carry flag register (15)
    uint16_t I_reg;                  // index register
    uint16_t pc_reg;                 // pc register

    uint16_t current_op;             // current opcode being executed by the system

    uint16_t stack[STACK_SIZE];      // stack
    uint16_t sp_reg;                 // stack pointer register

};


void load_rom(Chip8 *chip8, const char *rom_filename);
void init_system(Chip8 *chip8);

#endif // CHIP8_H
