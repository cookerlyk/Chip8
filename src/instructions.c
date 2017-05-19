#include "instructions.h"

/*
* Opcode 00EE: Return from subroutine
* pc_reg popped from top of stack, sp_reg decremented
*/
void return_from_subroutine(Chip8 *chip8) {
    chip8->sp_reg--;
    chip8->pc_reg = chip8->stack[chip8->sp_reg];
    chip8->pc_reg += 2;
}


/*
* Opcode 1NNN: Jump to address NNN
* pc_reg set to nnn
*/
void jump(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->pc_reg = nnn;
}


/*
* Opcode 2NNN: Call Subroutine at NNN
* sp_reg incremented, pc_reg pushed to stack, pc_reg set to NNN
*/
void call_subroutine(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->stack[chip8->sp_reg] = chip8->pc_reg;
    chip8->sp_reg++;
    chip8->pc_reg = nnn;
}


/*
* Opcode 3XKK: Skip next instruction
* Increments the pc_reg by 4 (2 instructions) if  V[x] == KK
*/
void se_Vx_kk(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;

    if (chip8->V[target_v_reg] == kk) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode 4XKK: Skip next instruction
* Increments the pc_reg by 4 (2 instructions) if  V[x] != KK
*/
void sne_Vx_kk(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;

    if (chip8->V[target_v_reg] != kk) {
        chip8->pc_reg += 4;
    }
    else {
        chip8->pc_reg += 2;
    }
}


/*
* Opcode 6XKK: Load Register Vx immediate
* Sets the V[X] register to byte KK
*/
void ld_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;

    chip8->V[target_v_reg] = kk;
    chip8->pc_reg += 2;
}


/*
* Opcode 7XKK: ADD Register Vx immediate
* Sets the V[X] register to V[X] + byte KK
*/
void add_Vx_imm(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    uint8_t vX_value = chip8->V[target_v_reg];
    
    chip8->V[target_v_reg] = vX_value + kk;;
    chip8->pc_reg += 2;
}


/*
* Opcode ANNN: Load I immediate
* Sets the Index register to the value of NNN
*/
void ldi(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->I_reg = nnn;
    chip8->pc_reg += 2;
}


/*
* Opcode CXKK: Random
* Generate Random Num between 0 - 255 then bitwise AND with value KK.
* Store the result in V[X]
*/
void rnd(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t kk = chip8->current_op & 0x00FF;
    uint8_t random_num = rand() % 256;

    chip8->V[target_v_reg] = random_num & kk;
    chip8->pc_reg += 2;
}


/*
* Opcode DXYN: Display N-byte sprite at ram[I_reg]
* Draws sprite at location X, Y. Set VF if collision
*/
void drw(Chip8 *chip8) {
    printf("Display not yet implemented...\n");
    chip8->pc_reg += 2;
}

