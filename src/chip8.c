#include "chip8.h"


// Load the rom into memory starting at location 0x200
int load_rom(Chip8 *chip8, const char *rom_filename) {
    int rom_length;
    uint8_t *rom_buffer;

    FILE *rom = fopen(rom_filename, "rb");
    if (rom != NULL) {
        // Get the size of the rom to allocate memory for a buffer
        fseek(rom, 0, SEEK_END);
        rom_length = ftell(rom); 
        rewind(rom);

        rom_buffer = (uint8_t*) malloc(sizeof(uint8_t) * rom_length);
        if (rom_buffer == NULL) {
            printf("ERROR: out of memory");
            return FALSE;
        }

        // TODO: handle error if not read into memory?
        fread(rom_buffer, sizeof(uint8_t), rom_length, rom); 

        // TODO: rom size verfication? 0xfff - 0x200 >= rom_length?
        for(int i = 0; i < rom_length; i++)
            chip8->ram[i + 0x200] = rom_buffer[i];
        }

    else {
        // TODO: handle the error better?
        printf("ERROR: File does not exist\n");
        return FALSE;
    }

    fclose(rom);
    free(rom_buffer);
    return TRUE;
}


/* 
* Initilize the system to its startup state, all of the 
* ram elements are set to 0, the stack is cleared, and the registers 
* are cleared. The PC register starts execution at location 0x200
* in memory
*/
void init_system(Chip8 *chip8) {
    chip8->pc_reg = PC_START;
    chip8->current_op = 0;
    chip8->sp_reg = 0;
    chip8->I_reg = 0;

    // TODO: Clear display

    // Clear stack
    for (int i = 0; i < STACK_SIZE; i++) {
        chip8->stack[i] = 0;
    }

    // Clear ram, calloc instead?
    for (int i = 0; i < TOTAL_RAM; i++) {
        chip8->ram[i] = 0;
    }

    // Clear registers
    for (int i = 0; i < NUM_V_REGISTERS; i++) {
        chip8->V[i] = 0;
    }

    // TODO: load fontset

    // Reset timers to their max values
    chip8->delay_timer = TIMER_MAX;
    chip8->sound_timer = TIMER_MAX;
}


uint16_t fetch_opcode(Chip8 *chip8) {
    uint16_t opcode;
    uint8_t msB = chip8->ram[chip8->pc_reg];
    uint8_t lsB = chip8->ram[chip8->pc_reg + 1];

    opcode = msB << 8 | lsB;

    return opcode;
}


void execute_instruction(Chip8 *chip8) {
    uint16_t opcode = fetch_opcode(chip8);
    chip8->current_op = opcode;

    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x00FF) {
                case 0x00EE:
                    printf("Instruction Return from Subroutine (00EE)\n");
                    return_from_subroutine(chip8);
                    break;
                default:
                    printf("ERROR: Unrecognized opcode 0x%X\n", opcode);
                    exit(EXIT_FAILURE);
                }
                break;

        case 0x1000:
            printf("Instruction Jump (1NNN)\n");
            jump(chip8);
            break;
        
        case 0x2000:
            printf("Instruction Call Subroutine (2NNN)\n");
            call_subroutine(chip8);
            break;

        case 0x3000:
            printf("Skip next instr Vx == kk (3XKK)\n");
            se_Vx_kk(chip8);
            break;

        case 0x4000:
            printf("Skip next instr Vx != kk (4XKK)\n");
            sne_Vx_kk(chip8);
            break;

        case 0x6000:
            printf("Instruction Load Vx reg (6XKK)\n");
            ld_Vx(chip8);
            break;

        case 0x7000:
            printf("Instruction ADD Vx reg immediate (7XKK)\n");
            add_Vx_imm(chip8);
            break;

        case 0xA000:
            printf("Instruction LDI (ANNN)\n");
            ldi(chip8);
            break;

        case 0xC000:
            printf("Instruction RNG Vx (CXKK)\n");
            rnd(chip8);
            break;

        case 0xD000:
            printf("Draw Sprite (DXYN)\n");
            drw(chip8);
            break;

        default:
            printf("ERROR: Unrecognized opcode 0x%X\n", opcode);
            exit(EXIT_FAILURE);
    }
}


void print_regs(Chip8 *chip8) {
    // print registers
    printf("Current OP: 0x%X\n", chip8->current_op);
    for (int i = 0; i < NUM_V_REGISTERS; i++) {
        printf("V Reg %X: 0x%X\n",i , chip8->V[i]);
    }
    printf("Index Reg: 0x%X\n", chip8->I_reg);
    printf("PC Reg: 0x%X\n", chip8->pc_reg);
    printf("SP Reg: 0x%X\n", chip8->sp_reg);
    printf("\n");

    // print stack
    // for (int i = 0; i < STACK_SIZE; i++) {
    //     printf("Stack Element %i: 0x%X\n",i , chip8->stack[i]);
    // }
}