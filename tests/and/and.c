#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int and(char* image_path[]){
    int ret_val = 0;
    int expected_result = 1;
    /* load object asm test file
       it contains the following asm code in binary:
            ADD R0, R0, 7   ; set R0 to B (1011)
            AND R1, R0, 9    ; set R1 to 9 (1001)
    */
    lc3_vm(2, image_path); // passing 2 instead of argc TODO: fix it later

    printf("AND test\t");

    // check if R0 contains expected result
    if(reg[R_R1] == expected_result){
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
