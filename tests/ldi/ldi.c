#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int ldi(char* image_path[]){
    int ret_val = 0;
    int expected_result = 0x666;
    /* load object asm test file
       it contains the following asm code in binary:
        LDI R0, SOME_LABEL
        HALT

        SOME_LABEL: .FILL x3010
    */

    // LDI will load the value stored on memory address 0x3010 (which is 0x666)
    memory[0x3010] = 0x666;

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if R0 contains expected_result
    if(reg[R_R0] == expected_result &&
       reg[R_COND] == FL_POS){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%#x\nResult in R0 is:\t%#x\t\t",
            expected_result, reg[R_R0]);

    return ret_val;
}
