#include "instructions.h"


/*
* Opcode 00E0: Clear the display
* Display (memory) is cleared
*/
void cls(Chip8 *chip8) {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            chip8->screen[i][j] = 0;
        }
    }
    chip8->pc_reg += 2;
}


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
* Opcode 5XY0: Skip next instruction
* Increments the pc_reg by 4 (2 instructions) if  V[x] == V[Y]
*/
void se_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;

    if (chip8->V[target_v_reg_x] == chip8->V[target_v_reg_y]) {
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
    
    // TODO: What if there is overflow?
    chip8->V[target_v_reg] = vX_value + kk;;
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY0: Load Vx, Vy
* Sets register V[X] to register V[Y]
*/
void move_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    uint8_t vY_value = chip8->V[target_v_reg_y];
    
    chip8->V[target_v_reg_x] = vY_value;
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY1: OR Vx, Vy
* V[X] | V[Y] result stored in V[X]
*/
void or_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    uint8_t regs_or = (chip8->V[target_v_reg_x] | chip8->V[target_v_reg_y]);

    chip8->V[target_v_reg_x] = regs_or;
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY2: AND Vx, Vy
* V[X] & V[Y] result stored in V[X]
*/
void and_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    uint8_t regs_and = (chip8->V[target_v_reg_x] & chip8->V[target_v_reg_y]);

    chip8->V[target_v_reg_x] = regs_and;
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY3: XOR Vx, Vy
* V[X] ^ V[Y] result stored in V[X]
*/
void xor_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    uint8_t regs_xor = (chip8->V[target_v_reg_x] ^ chip8->V[target_v_reg_y]);

    chip8->V[target_v_reg_x] = regs_xor;
    chip8->pc_reg += 2;
}


/*
* Opcode 8XY4: ADD Vx, Vy
* V[X] + V[Y] stored in V[X]
* If the sum is over 255, V[F] register (carry) is set to 1, else 0
* Only the bottom 8 bits of the sum are stored in the V[X] register
*/
void add_Vx_Vy(Chip8 *chip8) {
    uint8_t target_v_reg_x = (chip8->current_op & 0x0F00) >> 8;
    uint8_t target_v_reg_y = (chip8->current_op & 0x00F0) >> 4;
    uint16_t sum = (chip8->V[target_v_reg_x] + chip8->V[target_v_reg_y]);

    if (sum > 255) {
        chip8->V[0xF] = 1;
    }
    else {
        chip8->V[0xF] = 0;
    }

    chip8->V[target_v_reg_x] = (sum & 0xFF);
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
* Opcode BNNN: Jump + V[0]
* set pc_register to NNN + V[0]
*/
void jump_V0(Chip8 *chip8) {
    uint16_t nnn = chip8->current_op & 0x0FFF;

    chip8->pc_reg = (nnn + chip8->V[0]);
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


/*
* Opcode EX9E: Skip next instruction if key pressed
* Skips the next instruciton if the key with value V[X] is pressed
*/
void skp(Chip8 *chip8) {
    printf("Input not yet implemented...\n");
    chip8->pc_reg += 2;
}


/*
* Opcode EXA1: Skip next instruction if key not pressed
* Skips the next instruciton if the key with value V[X] is not pressed
*/
void sknp(Chip8 *chip8) {
    printf("Input not yet implemented...\n");
    chip8->pc_reg += 2;
}


/*
* Opcode FX07: Load Vx, DT
* V[X] set to value in delay_timer
*/
void ld_Vx_dt(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;

    chip8->V[target_v_reg] = chip8->delay_timer;
    chip8->pc_reg += 2;
}


/*
* Opcode FX15: Load DT, Vx
* delay_timer set to value V[X]
*/
void ld_dt_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t vX_value = chip8->V[target_v_reg];

    chip8->delay_timer = vX_value;
    chip8->pc_reg += 2;
}


/*
* Opcode FX18: Load ST, Vx
* sound_timer set to value V[X]
*/
void ld_st_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t vX_value = chip8->V[target_v_reg];

    chip8->sound_timer = vX_value;
    chip8->pc_reg += 2;
}


/*
* Opcode FX1E: Add I, VX
* Adds current I_reg and V[X], result stored in I_reg
*/
void add_i_Vx(Chip8 *chip8) {
    uint8_t target_v_reg = (chip8->current_op & 0x0F00) >> 8;
    uint8_t vX_value = chip8->V[target_v_reg];

    chip8->I_reg = chip8->I_reg + vX_value;
    chip8->pc_reg += 2;
}
