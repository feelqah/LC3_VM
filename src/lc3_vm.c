#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#include "lc3_vm.h"

uint16_t memory[UINT16_MAX];
uint16_t reg[R_COUNT];

uint16_t sign_extend(uint16_t x, int bit_count){
    if((x >> (bit_count - 1)) & 1){
        x |= (0xFFF << bit_count);
    }

    return x;
}

void update_flags(uint16_t r){
    if(reg[r] == 0){
        reg[R_COND] = FL_ZRO;
    }
    else if(reg[r] >> 15 ){ // 1 in the left-most bit indicates negative
        reg[R_COND] = FL_NEG;
    }
    else{
        reg[R_COND] = FL_POS;
    }
}

uint16_t check_key(){
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    return select(1, &readfds, NULL, NULL, &timeout) != 0;
}

void mem_write(uint16_t address, uint16_t val){
    memory[address] = val;
}

uint16_t mem_read(uint16_t address){
    if(address == MR_KBSR){
        if(check_key()){
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getchar();
        }
        else{
            memory[MR_KBSR] = 0;
        }
    }

    return memory[address];
}

struct termios original_tio;

void disable_input_buffering(){
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_input_buffering(){
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

void handle_interrupt(int signal){
    restore_input_buffering();
    printf("\n");
    exit(-2);
}

uint16_t swap16(uint16_t x){
    return (x << 8) | (x >> 8);
}

// Read image file
void read_image_file(FILE* file){
    // place image in memory
    uint16_t origin;

    fread(&origin, sizeof(origin), 1, file);
    origin = swap16(origin);

    // max file size known
    uint16_t max_read = UINT16_MAX - origin;
    uint16_t* p = memory + origin;

    size_t read = fread(p, sizeof(uint16_t), max_read, file);

    // swap to little endian
    while(read-- > 0){
        *p = swap16(*p);
        ++p;
    }
}

// Read image
int read_image(const char* image_path){
    FILE* file = fopen(image_path, "rb");

    if(!file) return 0;

    read_image_file(file);

    fclose(file);

    return 1;
}

void handle_instructions(){
    // set the PC to starting position
    // 0x3000 is the default
    enum{ PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    int running = 1;

    while(running){
        // Load instruction from memory at address from PC register
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch(op){
            case OP_ADD:
                {
                    // destination register DR
                    uint16_t r0 = (instr >> 9) & 0x7;
                    // first operand SR1
                    uint16_t r1 = (instr >> 6) & 0x7;
                    // check immediate mode
                    uint16_t imm_flag = (instr >> 5) & 0x1;

                    if(imm_flag){
                        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                        reg[r0] = reg[r1] + imm5;
                    }
                    else{
                        uint16_t r2 = instr & 0x7;
                        reg[r0] = reg[r1] + reg[r2];
                    }
                    update_flags(r0);
                }
                running = 0;
                break;

            case OP_AND:
                {
                    // destination register DR
                    uint16_t r0 = (instr >> 9) & 0x7;
                    // first operand SR1
                    uint16_t r1 = (instr >> 6) & 0x7;
                    // check immediate mode
                    uint16_t imm_flag = (instr >> 5) & 0x1;

                    if(imm_flag){
                        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                        reg[r0] = reg[r1] & imm5;
                    }
                    else{
                        uint16_t r2 = (instr >> 2) & 0x2; // TODO: check if this is correct
                        reg[r0] = reg[r1] & reg[r2];
                    }
                    update_flags(r0);
                }
                break;

            case OP_NOT:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;

                    reg[r0] = ~reg[r1];
                    update_flags(r0);
                }
                break;

            case OP_BR:
                {
                    uint16_t cond_flag = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    if(cond_flag & reg[R_COND]){
                        reg[R_PC] += pc_offset;
                    }
                }

                break;

            case OP_JMP:
                {
                    // also handles RET
                    uint16_t base = (instr >> 6) & 0x7;
                    reg[R_PC] = R[base];
                }
                break;

            case OP_JSR:
                {
                    uint16_t flag = (instr >> 11) & 1;
                    reg[R_R7] = reg[R_PC];

                    if(flag){
                        uint16_t pc_offset = sign_extend(instr & 0x7FF, 11);
                        reg[R_PC] += pc_offset; // JSR
                    }
                    else{
                        uint16_t base = (instr >> 6) & 0x7;
                        reg[R_PC] = reg[base]; // JSRR
                    }
                }
                break;

            case OP_LD:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

                    reg[r0] = mem_read(reg[R_PC] + pc_offset);
                    update_flags(r0);
                }
                break;

            case OP_LDI:
                {
                    // destination register
                    uint16_t r0 = (instr >> 9) & 0x7;
                    // PCoffset 9
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    // add pc_offset to the current PC and look at that 
                    // memory location for that address
                    reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset));
                    update_flags(r0);
                }
                break;

            case OP_LDR:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t base = (instr >> 6) & 0x7;
                    uint16_t offset = sign_extend(instr & 0x3F, 6);

                    reg[r0] = mem_read(reg[base] + offset);
                    update_flags(r0);
                }
                break;

            case OP_LEA:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 1FF, 9);

                    reg[r0] = reg[R_PC] + pc_offset;
                    update_flags(r0);
                }
                break;

            case OP_ST:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

                    mem_write(reg[R_PC] + pc_offset, reg[r0]);
                }
                break;

            case OP_STI:
                // TODO
                break;

            case OP_STR:
                // TODO
                break;

            case OP_TRAP:
                // TODO
                break;

            case OP_RES:
            case OP_RTI:
            default:
                //TODO: BAD OPCODE
                break;
        }
    }
}

void setup_terminal_input(){
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();
}

void load_arguments(int argc, char* argv[]){
    // expecting one or more VM image paths
    if(argc < 2){
        // show usage string
        printf("lc3_vm [path_to_image_file1] ...\n");
        exit(2);
    }

    for(int j=1;j<argc;j++){
        if(!read_image(argv[j])){
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }
}

void lc3_vm(int argc, char* argv[]){
    // Load arguments
    load_arguments(argc, argv);

    // Setup
    setup_terminal_input();

    // Handle instructions
    handle_instructions();

    // Shutdown
    restore_input_buffering();
}

