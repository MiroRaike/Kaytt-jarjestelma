#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("my-zip: searchterm [file ...]\n");
        exit(1);
    }
    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL){
        printf("File not found\n");
        exit(1);
    }

    int size;

    // For this I thought that getting the file size would be the easiest way to make the looping work.
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    // 
    fseek(fp, 0, SEEK_SET);
    printf("%d size is this \n",size);
    if((size % 5) != 0){
        printf("size isn't divicible by 5, zipped file is corrupted\n");
        exit(1);
    }

    size = size / 5;

    FILE *uncompressed;

    uncompressed = fopen(argv[2], "w");

    int loops;
    int binCharacter;

    for(int i=0;i<size;i++){
        if((fread(&loops, 4, 1, fp)!=1)){
            printf("Error reading file");
            exit(1);
        };
        if((fread(&binCharacter, 1, 1, fp)!=1)){
            printf("Error reading file");
        };
        for(int x=0;x<loops;x++){
            fprintf(uncompressed,"%c",binCharacter);
        }
    }

    
    printf("Finished unzip:ing file\n");
    fclose(fp);
    fclose(uncompressed);
    return 0;
}