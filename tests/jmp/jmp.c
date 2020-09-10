#include <stdio.h>
#include <stdint.h>

#include "lc3_vm.h"

int jmp(char* image_path[]){
    int ret_val = 0;
    int expected_result = 0;
    /* load object asm test file
       it contains the following asm code in binary:
       JMP R0               ; R0 contains the address where HALT is located
       ADD R1, R1, 0        ; dummy instruction which we will skip
       HALT

    */
    /* set register R0 to 0x3002 (to the second instruction in the asm file,
        which is HALT)
       call lc3_vm with image of jmp.obj
       check if PC is now at 0x3003 (HALT is actually at 0x3002 but the PC
       was already incremented before the HALT instruction

     */
    expected_result = 0x3002;
    reg[R_R0] = expected_result;

    lc3_vm(2, image_path); // passing 2 instead of argc

    // check if PC contains value from R0
    if((reg[R_PC]) == expected_result + 1){
        // pass
        ret_val = 1;
    }

    printf("Expected result is:\t%#x\nResult in PC is:\t%#x\t\t",
            expected_result + 1, reg[R_PC]);

    return ret_val;
}
