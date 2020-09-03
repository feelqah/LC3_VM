#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int add(char* image_path[]){
    /* load object asm test file
       it contains the following asm code in binary:
            ADD R0, R0, 5
    */
    int ret_val = 0;
    int expected_result = reg[R_R0] + 5; // R0 can already contain some value

    lc3_vm(2, image_path); // passing 2 instead of argc

    printf("ADD test\t");

    // check if R0 contains expected result
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
