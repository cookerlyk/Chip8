/*
*
* Definition of the chip8 struct and some constants 
* to be used by the program. 
*
*/

#define NUM_V_REGISTERS 16
#define TOTAL_RAM 4096
#define STACK_SIZE 16
#define PC_START 0x200
#define TIMER_MAX 255

#define TRUE 1
#define FALSE 0


typedef struct Chip8_t Chip8;

struct Chip8_t {
    uint8_t ram[TOTAL_RAM];          // 4k of memory
    uint16_t stack[STACK_SIZE];      // stack, stores up to 16 levels

    // registers 
    uint8_t V[NUM_V_REGISTERS];      // general purpose registers (0 - 14) and the carry flag register (15)
    uint16_t I_reg;                  // index register
    uint16_t pc_reg;                 // pc register
    uint16_t sp_reg;                 // stack pointer register

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint16_t current_op;             // current opcode being executed by the system

};
