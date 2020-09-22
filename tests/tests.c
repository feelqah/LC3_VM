#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

char* change_extension(char* path, char* extension){
    size_t len = strlen(path);
    char* temp_path = malloc(sizeof(char) * len);

    // strip .obj from file path
    strncpy(temp_path, path, len-3);

    // add extension to path
    strcat(temp_path, extension);

    return temp_path;
}

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

        // image_path contains .obj file, we need to print .asm instead
        char* asm_file_path = change_extension(image_path[1], "asm");

        printf("Assembly code of test:\n");
        print_file(asm_file_path);

        free(asm_file_path);

        if(strstr(image_path[1], "/add") != NULL){
            if(add(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/and") != NULL){
            if(and(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/not") != NULL){
            if(not(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/br") != NULL){
            if(br(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/jmp") != NULL){
            if(jmp(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/jsr") != NULL){
            if(jsr(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/ldi") != NULL){
            if(ldi(image_path)){
               printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/ldr") != NULL){
            if(ldr(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/ld") != NULL){
            if(ld(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/lea") != NULL){
            if(lea(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/sti") != NULL){
            if(sti(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/str") != NULL){
            if(str(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/st") != NULL){
            if(st(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
         }

        else if(strstr(image_path[1], "/trap_getc") != NULL){
            if(trap_getc(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/trap_out") != NULL){
            if(trap_out(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/trap_puts") != NULL){
            if(trap_puts(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
       }

        else if(strstr(image_path[1], "/trap_in") != NULL){
            if(trap_in(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/trap_putsp") != NULL){
            if(trap_putsp(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else if(strstr(image_path[1], "/trap_halt") != NULL){
            if(trap_halt(image_path)){
                printf("[PASS]\n");
            }
            else{
                printf("[FAIL]\n");
            }
        }

        else{
            printf("Test not found!\n");
            printf("'%s' doesn't exist\n", image_path[1]);
        }

        printf("%s\n\n", "==============================================");

    } // End of for loop

    return 0;
}
