#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "chip8_t.h"

// instructions are listed in the order of their opcodes

void return_from_subroutine(Chip8 *chip8);
void jump(Chip8 *chip8);
void call_subroutine(Chip8 *chip8);
void se_Vx_kk(Chip8 *chip8);
void sne_Vx_kk(Chip8 *chip8);
void ld_Vx(Chip8 *chip8);
void add_Vx_imm(Chip8 *chip8);
void ldi(Chip8 *chip8);
void rnd(Chip8 *chip8);


void drw(Chip8 *chip8);

#endif // INSTRUCTIONS_H
