#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int ldr(char* image_path[]){
    int ret_val = 0;
    int expected_result = 0x666;
    /* load object asm test file
       it contains the following asm code in binary:
        LD R0, ADDRESS
        LDR R1, R0, 1

        ADDRESS: .FILL x3008
    */

    // set value of 0x666 at memory address 0x3009
    memory[0x3009] = expected_result;

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if R1 contains expected_result
    if(reg[R_R1] == expected_result &&
       reg[R_COND] == FL_POS){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%#x\nResult in R1 is:\t%#x\t\t",
            expected_result, reg[R_R1]);

    return ret_val;
}
