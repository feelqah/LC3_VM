#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int jsr(char* image_path[]){
    int ret_val = 0;
    int expected_result = 0x3001;
    /* load object asm test file
       it contains the following asm code in binary:
            JSR SOME_LABEL
            SOME_LABEL: HALT
    */
    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if R7 contains address where HALT is (0x3001)
    // and check if PC is now at above address + 1
    if(reg[R_R7] == expected_result &&
       reg[R_PC] == expected_result + 1){
        // pass
        ret_val = 1;
    }

    printf("Expected result for R7 is:\t%#x\nResult in R7:\t%#x\n",
            expected_result, reg[R_R7]);

    printf("Expected result for PC is:\t%#x\nResult in PC:\t%#x\t\t",
            expected_result+1, reg[R_PC]);

    return ret_val;
}
