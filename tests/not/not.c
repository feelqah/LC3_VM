#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int not(char* image_path[]){
    int ret_val = 0;
    int expected_result = 0xFFFF; // 1111111111111111
    /* load object asm test file
       it contains the following asm code in binary:
        NOT R0, R1
    */
    // set value of R1 to 1001
    reg[R_R1] = 0; // 0000000000000000

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if R0 contains expected_result
    if(reg[R_R0] == expected_result){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%#x\nResult in R0 is:\t%#x\t\t",
            expected_result, reg[R_R0]);

    return ret_val;
}
