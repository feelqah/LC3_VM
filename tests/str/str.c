#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int str(char* image_path[]){
    int ret_val = 0;
    int expected_result = 666;
    int address = 0x3100;
    /* load object asm test file
       it contains the following asm code in binary:
        STR R1, R2, 0
        HALT
    */
    reg[R_R1] = expected_result;    // value that will be stored at address from R2
    reg[R_R2] = address;

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if R0 contains 1
    if(memory[address] == expected_result){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%d\nExpected value at address %#x is:\t%d\t\t",
            expected_result, address, memory[address]);

    return ret_val;
}
