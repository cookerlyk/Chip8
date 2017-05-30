#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "chip8_t.h"

// instructions are listed in the order of their opcodes

void cls(Chip8 *chip8);                         // 00E0
void return_from_subroutine(Chip8 *chip8);      // 00EE
void jump(Chip8 *chip8);                        // 1NNN
void call_subroutine(Chip8 *chip8);             // 2NNN
void se_Vx_kk(Chip8 *chip8);                    // 3XKK
void sne_Vx_kk(Chip8 *chip8);                   // 4XKK
void se_Vx_Vy(Chip8 *chip8);                    // 5XY0
void ld_Vx(Chip8 *chip8);                       // 6XKK
void add_Vx_imm(Chip8 *chip8);                  // 7XKK
void move_Vx_Vy(Chip8 *chip8);                  // 8XY0
void or_Vx_Vy(Chip8 *chip8);                    // 8XY1
void and_Vx_Vy(Chip8 *chip8);                   // 8XY2
void xor_Vx_Vy(Chip8 *chip8);                   // 8XY3
void add_Vx_Vy(Chip8 *chip8);                   // 8XY4
void sub_Vx_Vy(Chip8 *chip8);                   // 8XY5
void shr(Chip8 *chip8);                         // 8XY6
void subn_Vx_Vy(Chip8 *chip8);                  // 8XY7
void shl(Chip8 *chip8);                         // 8XYE
void sne_Vx_Vy(Chip8 *chip8);                   // 9XY0
void ldi(Chip8 *chip8);                         // ANNN
void jump_V0(Chip8 *chip8);                     // BNNN
void rnd(Chip8 *chip8);                         // CXKK
void drw(Chip8 *chip8);                         // DXYN
void skp(Chip8 *chip8);                         // EX9E
void sknp(Chip8 *chip8);                        // EXA1
void ld_Vx_dt(Chip8 *chip8);                    // FX07
void ld_Vx_k(Chip8 *chip8);                     // FX0A
void ld_dt_Vx(Chip8 *chip8);                    // FX15
void ld_st_Vx(Chip8 *chip8);                    // FX18
void add_i_Vx(Chip8 *chip8);                    // FX1E
void ld_F_Vx(Chip8 *chip8);                     // FX29
void st_bcd_Vx(Chip8 *chip8);                   // FX33
void st_V_regs(Chip8 *chip8);                   // FX55
void ld_V_regs(Chip8 *chip8);                   // FX65


#endif // INSTRUCTIONS_H
