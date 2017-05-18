#include "instructions.h"

/*
* Opcode ANNN: Sets the Index register to the value of NNN
*/
void ANNN(Chip8 *chip8) {
    uint16_t value = chip8->current_op & 0x0FFF;
    chip8->I_reg = value;

    chip8->pc_reg += 2;
}
