#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int add(char* image_path[]){
    int ret_val = 0;
    /* load object asm test file
       it contains the following asm code in binary:
            ADD R0, R0, 5
    */

    int expected_result = reg[R_R0] + 5;

    lc3_vm(2, image_path); // passing 2 instead of argc

    printf("ADD test\t");

    // check if R0 contains 1
    if(reg[R_R0] == expected_result){
        // pass
        printf("[PASS]\n");
        ret_val = 1;
    }
    else{
        // fail
        printf("[FAIL]\n");
        ret_val = 0;
    }

    return ret_val;
}
