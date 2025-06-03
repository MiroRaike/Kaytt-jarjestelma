#include <stdio.h>
#include <stdlib.h>

// Instead of fgets, I decided to use getc instead because it's technically a bit more efficient and I don't have to manually allocate
// memory for the buffer. I also don't have to worry about the buffer size this way.

int main(int argc, char* argv[]){

    char character;

    if(argc < 2){
        printf("my-cat: file [file ...]\n");
        exit(0);
    }

    for(int i = 1; i < argc; i++){
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-cat: cannot open file\n");
            exit(1);
        }
        printf("Reading file %s\n\n", argv[i]);
        while((character = (getc(fp))) != EOF){
            putchar(character);
        }
        printf("\nFinished reading file %s\n\n", argv[i]);
        fclose(fp);
    }
    return 0;
}