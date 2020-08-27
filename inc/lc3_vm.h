// TODO: Add documentation
/* 65536 locations */
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
	R_PC, // program counter
	R_COND,
	R_COUNT
};

/* Register Storage  */
uint16_t reg[R_COUNT];

enum{
	FL_POS = 1 << 0, // P
	FL_ZRO = 1 << 1, // Z
	FL_NEG = 1 << 2  // N
};

/* Memory Mapped Registers*/
enum{
	MR_KBSR = 0xFE00,	// keyboard status
	MR_KBDR = 0xFE02	// keyboard data
};

/* Opcodes */
enum{
	OP_BR = 0,	// branch
	OP_ADD,			// add
	OP_LD,			// load
	OP_ST,			// store
	OP_JSR,			// jump register
	OP_AND,			// bitwise and
	OP_LDR,			// load register
	OP_STR,			// store register
	OP_RTI,			// unused
	OP_NOT,			// bitwise not
	OP_LDI, 		// load indirect
	OP_STI,			// store indirect
	OP_JMP,			// jump
	OP_RES,			// reserved (unused)
	OP_LEA,			// load effective address
	OP_TRAP			// execute trap
};

/* Function declarations */

int read_image(const char* image_path);

void read_image_file(FILE* file);

uint16_t swap16(uint16_t x);

void handle_interrupt(int signal);

void restore_input_buffering(void);

void disable_input_buffering(void);

uint16_t mem_read(uint16_t address);

uint16_t check_key(void);

void update_flags(uint16_t r);

uint16_t sign_extend(uint16_t x, int bit_count);

