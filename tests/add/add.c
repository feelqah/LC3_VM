// AND R0, R0, 0        ; Clear R0
// AND R0, R0, 1        ; Add 1 to R0 and store back in R0
#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int add(char* image_path[]){
    int ret_val = 0;
    /* load object asm test file
       it contains the following asm code in binary:
            AND R0, R0, 0
            AND R0, R0, 1
    */
    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if R0 contains 1
    if(reg[R_R0] == 1){
        // pass
        printf("Test: ADD\nPass!\n");
        ret_val = 1;
    }
    else{
        // fail
        printf("Test: ADD\nFail!\n");
        ret_val = 0;
    }

    return ret_val;
}
