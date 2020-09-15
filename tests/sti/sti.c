#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int sti(char* image_path[]){
    int ret_val = 0;
    int expected_result = 666;
    int address = 0x3100;
    /* load object asm test file
       it contains the following asm code in binary:
       STI R5, ADDRESS
       HALT

       ADDRESS: .FILL x3100
    */
    reg[R_R5] = expected_result;

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if value at memory location 0x3100 contains expected_result
    if(memory[address] == expected_result){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%d\nExpected value at address %#x is:\t%d\t\t",
            expected_result, address, memory[address]);

    return ret_val;
}
