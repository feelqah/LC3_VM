#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int and(char* image_path[]){
    /* load object asm test file
       it contains the following asm code in binary:
            AND R0, R0, x0   ; clear R0
            ADD R0, R0, 7    ; set R0 to 7 (1011)
            AND R1, R0, 9    ; AND R0 with 9 (1001)and store (result:1)in R1
    */
    int ret_val = 0;
    int expected_result = 1;

    lc3_vm(2, image_path); // passing 2 instead of argc

    printf("\nAND test\t");
    printf("ADD R0, R0, x0\t; clear R0\n");
    printf("ADD R0, R0, 7\t; set R0 to 7 (1011)\n");
    printf("AND R1, R0, 9\t; AND R0 with 9 (1001) and store (result: 1) in R1");

    // check if R1 contains expected result
    if(reg[R_R1] == expected_result){
        // pass
        printf("Expected result is:\t%d\nResult in R1 is:\t%d\t\t[PASS]\n",
                expected_result, reg[R_R1]);
        ret_val = 1;
    }
    else{
        // fail
        printf("Expected result is:\t%d\nResult in R1 is:\t%d\t\t[FAIL]\n",
                expected_result, reg[R_R1]);
        ret_val = 0;
    }

    return ret_val;
}
