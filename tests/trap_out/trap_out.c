#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int trap_out(char* image_path[]){
    int ret_val = 0;
    char* expected_result = "a";
    /* load object asm test file
       it contains the following asm code in binary:
        TRAP 0x21
        HALT
    */

    char in_buffer[] = {0};
    FILE *in = fmemopen(in_buffer, sizeof(in_buffer), "r");

    char out_buffer[256];
    FILE *out = fmemopen(out_buffer, sizeof(out_buffer), "wb+");

    load_arguments(2, image_path);
    setup_terminal_input();

    reg[R_PC] = 0x3000;
    uint16_t instr = mem_read(reg[R_PC]++);

    reg[R_R0] = expected_result[0];

    execute_trap(instr, in, out);

    restore_input_buffering();

    // check if out contains value from R0
    if(reg[R_R0] == out_buffer[0]){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%c\nResult in output buffer is:\t%c\t\t",
            expected_result[0], out_buffer[0]);

    fclose(in);
    fclose(out);

    return ret_val;
}
