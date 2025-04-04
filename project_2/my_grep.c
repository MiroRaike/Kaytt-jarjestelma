#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX 1000

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    if(argc < 3){
        char line[MAX];
        printf("my-grep: searchterm\n");
        fgets(line, MAX, stdin);
        // if you want to loop this just steal the code from project_1 reverse.c with manually allocating lines
        if(strstr(line, argv[1])){
            printf("%s", line);
        }
    }else{

        char *line = NULL;
        size_t len = 0;

        FILE *fp = fopen(argv[2], "r");

        if(fp == NULL){
            perror("my-grep: cannot open file\n");
            exit(1);
        }

        while(getline(&line, &len, fp) != -1){
            if(strstr(line, argv[1])){
                printf("%s", line);
            }
        }
        fclose(fp);
        free(line);
    }
    return 0;
}
