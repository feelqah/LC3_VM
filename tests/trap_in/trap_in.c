#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int trap_in(char* image_path[]){
    int ret_val = 0;
    /* load object asm test file
       it contains the following asm code in binary:
        TRAP x23
        HALT
    */

    char in_buffer[] = {"a"};
    FILE *in = fmemopen(in_buffer, sizeof(in_buffer), "r");

    char out_buffer[256];
    FILE *out = fmemopen(out_buffer, sizeof(out_buffer), "w");

    load_arguments(2, image_path);
    setup_terminal_input();

    reg[R_PC] = 0x3000;
    uint16_t instr = mem_read(reg[R_PC]++);

    execute_trap(instr, in, out);

    restore_input_buffering();

    // check if R0 contains 'a'
    if(reg[R_R0] == 97){ // 97 = 'a' in ASCII
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%s\nResult in R0 is:\t%c\t\t",
           "a", reg[R_R0]);

    fclose(in);
    fclose(out);

    return ret_val;
}
