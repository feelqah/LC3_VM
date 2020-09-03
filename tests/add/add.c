#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"
#include "tests.h"

int add(char* image_path[]){
    /* load object asm test file
       it contains the following asm code in binary:
            ADD R0, R0, 5
    */
    int ret_val = 0;
    int expected_result = 5;

    lc3_vm(2, image_path); // passing 2 instead of argc

    print_file("tests/add/add.asm");

    // check if R0 contains expected result
    if(reg[R_R0] == expected_result){
        // pass
        printf("Expected result is:\t%d\nResult in R0 is:\t%d\t\t[PASS]\n",
                expected_result, reg[R_R0]);
        ret_val = 1;
    }
    else{
        // fail
        printf("Expected result is:\t%d\nResult in R0 is:\t%d\t\t[FAIL]\n",
                expected_result, reg[R_R0]);
        ret_val = 0;
    }

    return ret_val;
}
