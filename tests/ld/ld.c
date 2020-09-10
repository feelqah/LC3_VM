#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int ld(char* image_path[]){
    int ret_val = 0;
    int expected_result = 0x666;
    /* load object asm test file
       it contains the following asm code in binary:

        LD R0, SOME_LABEL
        SOME_LABEL: HALT    ; 0x3001 address
    */
    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if R0 contains 1
    if(reg[R_R0] == expected_result &&
       reg[R_COND] == FL_POS){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%#x\nResult in R0 is:\t%#x\t\t",
            expected_result, reg[R_R0]);

    return ret_val;
}
