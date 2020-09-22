#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int br(char* image_path[]){
    /* load object asm test file
       it contains the following asm code in binary:
            BRp SOME_LABEL
            SOME_LABEL: HALT
    */
    // BR SOME_LABEL
    // Branch to label
    // Check if PC register incremented by 2 (label is second instruction)

    int ret_val = 0;

    /* the PC offset after we run the asm code is 2 because we only have two instructions (the label
       with HALT instruction is the next instruction after branch):
        we start at address 0x3000 then we load the BR instruction
        at address 0x3001 after that we jump to the label and load
        the HALT instruction which is at address 0x3002 (the offset of
        branch instruction is 0 in this case)
     */
    int pc_offset = 2;

    int expected_result = 0x3000 + pc_offset;

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if Program counter register is now at expected_result
    if(reg[R_PC] == expected_result){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%#x\nResult in PC is:\t%#x\t\t",
            expected_result, reg[R_PC]);

    return ret_val;
}
