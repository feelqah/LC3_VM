// TODO: Remove hardcoded paths to test images
#include <string.h>
#include <stdio.h>

#include "tests.h" // TODO: maybe add a tests header

int main(int argc, char* argv[]){
    // TODO: handle flags
    
    /*
     example usage:
        ./run_tests "path_to_add.obj"
     */

    // second argument defines path of image
    char* image_path = argv[1];

    if(strstr(image_path, "add.obj") != 0){

        printf("ADD test\n");
        add(argv);
    }

    else if(strstr(image_path, "and.obj") == 0){
        printf("AND test\n");
    }
    // TODO: Handle running all tests at once
    else{
        printf("%s doesn't exist\n", image_path);
    }

    return 0;
}
