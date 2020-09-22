#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "lc3_vm.h"

int trap_puts(char* image_path[]){
    int ret_val = 0;
    /* load object asm test file
       it contains the following asm code in binary:
        TRAP x22
        HALT
    */

    char in_buffer[] = {0};
    FILE *in = fmemopen(in_buffer, sizeof(in_buffer), "r");

    char out_buffer[256];
    FILE *out = fmemopen(out_buffer, sizeof(out_buffer), "w");

    load_arguments(2, image_path);
    setup_terminal_input();

    reg[R_PC] = 0x3000;
    uint16_t instr = mem_read(reg[R_PC]++);

    reg[R_R0] = 0x3101;

    memory[0x3101] = 116; // t
    memory[0x3102] = 101; // e
    memory[0x3103] = 115; // s
    memory[0x3104] = 116; // t
    memory[0x3105] = 0;

    execute_trap(instr, in, out);

    restore_input_buffering();

    // check if output buffer contains string 'test'
    if(strncmp(out_buffer, "test", 4) == 0){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%s\nResult in output buffer is:\t%s\t\t",
            "test", out_buffer);

    fclose(in);
    fclose(out);

    return ret_val;
}
