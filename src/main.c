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

/* 65536 locations  */
uint16_t memory[UINT16_MAX];

/* Registers */
enum{
	R_R0 = 0,
	R_R1,
	R_R2,
	R_R3,
	R_R4,
	R_R5,
	R_R6,
	R_R7,
	R_PC,   // program counter
	R_COND,
	R_COUNT
};

/* Condition Flags*/
enum{
	FL_POS = 1 << 0, // P
	FL_ZRO = 1 << 1, // Z
	FL_NEG = 1 << 2  // N
};

/* Memory Mapped Registers */
enum{
	MR_KBSR = 0xFE00, //
	MR_KBDR = 0xFE02  // keyboard data
};

uint16_t reg[R_COUNT];

/* Opcodes */
enum{
	OP_BR = 0, // branch
	OP_ADD,		 // add
	OP_LD,		 // load
	OP_ST,		 // store
	OP_JSR,		 // jump register
	OP_AND,		 // bitwise and
	OP_LDR,		 // load register
	OP_STR,		 // store register
	OP_RTI,		 // unused
	OP_NOT,		 // bitwise not
	OP_LDI,		 // load indirect
	OP_STI,		 // store indirect
	OP_JMP,		 // jump
	OP_RES,		 // reserved (unused)
	OP_LEA,		 // load effective address
	OP_TRAP		 // execute trap
};



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

int main(int argc, const char* argv[]){
	// Load arguments
	// expecting one or more paths to VM images
	if(argc<2){
		//show usage string
		printf("lc3_vm [image_file1] ...\n");
		exit(2);
	}

	for(int j=1;j<argc;++j){
		if(!read_image(argv[j])){
			printf("failed to load image: %s\n", argv[j]);
			exit(1);
		}
	}

	// Setup
	signal(SIGINT, handle_interrupt);
	disable_input_buffering();

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

				break;

			case OP_AND:
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
				break;

		  case OP_NOT:
				uint16_t r0 = (instr >> 9) & 0x7;
				uint16_t r1 = (instr >> 6) & 0x7;

				reg[r0] = ~reg[r1];
				update_flags(r0);

				break;

			case OP_BR:
				uint16_t cond_flag = (instr >> 9) & 0x7;
				uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
				if(cond_flag & reg[R_COND]){
					reg[R_PC] += pc_offset;
				}

				break;

			case OP_JMP:
				// TODO
				break;

			case OP_JSR:
				// TODO
				break;

			case OP_LD:
				// TODO
				break;

			case OP_LDI:
				// destination register
				uint16_t r0 = (instr >> 9) & 0x7;
				// PCoffset 9
				uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
				// add pc_offset to the current PC and look at that memory location
				// for the final address
				reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset));
				update_flags(r0);
				break;

			case OP_LDR:
				// TODO
				break;

			case OP_LEA:
				// TODO
				break;

			case OP_ST:
				// TODO
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

	// Shutdown
	restore_input_buffering();
}
