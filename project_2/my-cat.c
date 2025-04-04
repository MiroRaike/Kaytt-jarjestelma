#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    char character;

    for(int i = 1; i < argc; i++){
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror("Error opening the file\n");
            exit(1);
        }
        printf("Reading file %s\n\n", argv[i]);
        while((character = (getc(fp))) != EOF){
            putchar(character);
        }
        printf("\nFinished reading file %s\n\n", argv[i]);
    }
    return 0;
}
