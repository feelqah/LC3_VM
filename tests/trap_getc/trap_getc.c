#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int trap_getc(char* image_path[]){
    int ret_val = 0;
    int expected_result = 97; // a in ASCII
    /* load object asm test file
       it contains the following asm code in binary:
       TRAP x20
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


    // check if R0 contains expected result
    if(reg[R_R0] == expected_result){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%d\nResult in R0 is:\t%d\t\t",
            expected_result, reg[R_R0]);

    fclose(in);
    fclose(out);

    return ret_val;
}
