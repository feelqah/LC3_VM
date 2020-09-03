#include <string.h>
#include <stdio.h>

#include "tests.h"


int print_file(char* path){
    int c = 0;
    FILE* file = fopen(path, "r");

    if(!file) return 0;

    while((c = getc(file)) != EOF){
        putchar(c);
    }

    fclose(file);
    return 1;
}

int main(int argc, char* argv[]){
    /*
     example usage:
        ./run_tests path_to_test.obj path_to_test2.obj ...
     */

    for(int i=1;i<argc;i++){
        char* image_path[2]; // adapted for lc3_vm function which takes argv

        // second argument defines path of image
        image_path[0] = argv[0];
        image_path[1] = argv[i];

        printf("Running test for: %s\n", image_path[1]);

        if(strstr(image_path[1], "/add") != NULL){
            add(image_path);
            printf("\n");
        }

        else if(strstr(image_path[1], "/and") != NULL){
            and(image_path);
            printf("\n");
        }
    }
/*
    else if(strstr(image_path, "not.obj") == 0){
        printf("NOT test\t");

        if(not(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "br.obj") == 0){
        printf("BR test\t");

        if(br(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "jmp.obj") == 0){
        printf("JMP test\t");

        if(jmp(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "jsr.obj") == 0){
        printf("JSR test\t");

        if(jsr(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "ld.obj") == 0){
        printf("LD test\t");

        if(ld(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "ldi.obj") == 0){
        printf("LDI test\t");

        if(ldi(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "ldr.obj") == 0){
        printf("LDR test\t");

        if(ldr(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "lea.obj") == 0){
        printf("LEA test\t");

        if(lea(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "st.obj") == 0){
        printf("ST test\t");

        if(st(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "sti.obj") == 0){
        printf("STI test\t");

        if(sti(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "str.obj") == 0){
        printf("STR test\t");

        if(str(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "trap_getc.obj") == 0){
        printf("TRAP GETC test\t");

        if(trap_getc(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "trap_out.obj") == 0){
        printf("TRAP OUT test\t");

        if(trap_out(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "trap_puts.obj") == 0){
        printf("TRAP PUTS test\t");

        if(trap_puts(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "trap_in.obj") == 0){
        printf("TRAP IN test\t");

        if(trap_in(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "trap_putsp.obj") == 0){
        printf("TRAP PUTSP test\t");

        if(trap_putsp(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "trap_halt.obj") == 0){
        printf("TRAP HALT test\t");

        if(trap_halt(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "res.obj") == 0){
        printf("RES test\t");

        if(res(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else if(strstr(image_path, "rti.obj") == 0){
        printf("RTI test\t");

        if(rti(argv)){
            printf("[Pass]\n");
        }
        else{
            printf("[Fail]\n");
        }
    }

    else{
        printf("Test not found!\n");
        printf("'%s' doesn't exist\n", image_path);
    }
    */
    return 0;
}
