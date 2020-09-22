#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "lc3_vm.h"

int trap_putsp(char* image_path[]){
    int ret_val = 0;
    /* load object asm test file
       it contains the following asm code in binary:
        TRAP x24
        HALT
    */

    char in_buffer[] = {};
    FILE *in = fmemopen(in_buffer, sizeof(in_buffer), "r");

    char out_buffer[256];
    FILE *out = fmemopen(out_buffer, sizeof(out_buffer), "w");

    load_arguments(2, image_path);
    setup_terminal_input();

    reg[R_PC] = 0x3000;
    uint16_t instr = mem_read(reg[R_PC]++);

    reg[R_R0] = 0x3100;
    memory[0x3100] = 97 | (97 << 8); // 'a' in ASCII; place one in 7:0
                                     // other in [15:8]

    execute_trap(instr, in, out);

    restore_input_buffering();

    // check if output buffer contains "aa"
    if(strncmp(out_buffer, "aa", 2) == 0){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%s\nResult in output buffer is:\t%s\t\t",
            "aa", out_buffer);

    fclose(in);
    fclose(out);

    return ret_val;
}
