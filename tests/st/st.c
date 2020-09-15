#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int st(char* image_path[]){
    int ret_val = 0;
    int expected_result = 666;
    /* explanation of address var:
            label location (0x3002) - instruction location (0x3000) - 1
            = pc_offset (1)
        this pc_offset is then added to the current PC (0x3001) and
        the contents of R5 are stored into 0x3002

        The value (x3100) pointed by SOME_LABEL is ignored here,
        but the actual address where SOME_LABEL is used (0x3002)
     */
    int address = 0x3002;

    /* load object asm test file
       it contains the following asm code in binary:
        ST R5, SOME_LABEL
        HALT

        SOME_LABEL: x3100
    */
    reg[R_R5] = expected_result; // the value to be stored at 0x3002

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if expected result is at 0x3002
    if(memory[address] == expected_result){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%d\nExpected result in memory at address %#x"
            " is:\t%d\t\t", expected_result, address, memory[address]);

    return ret_val;
}
