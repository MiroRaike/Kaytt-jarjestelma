#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char error_message[30] = "An error has occurred\n";

int create_fork(char *line){
    int status;
    char* ptr = line;
    char* token;
    // First we remove the new line character
    // execvp just does not work if it's included
    token = strtok_r(line, "\n", &ptr);
    ptr = token;

    // Here we split the line into parrael commands and fork them at the same time.
    while((token = strtok_r(ptr, "&", &ptr))){
        printf("Lineargs: %s\n", token);
        pid_t pid = fork();
        switch (pid) {
            case -1:              /* error in fork */
                write(STDERR_FILENO, error_message, strlen(error_message));
                exit(1);
            case 0:
                char *lineargs[20];
                char* ptr = token;
                char* token2;
                int i = 0;
            
                printf("Line: %s\n", token);
            
                while((token2 = strtok_r(ptr, " ", &ptr))){
                    printf("Looping\n");
                    lineargs[i] = token2;
                    printf("Lineargs: %s\n", lineargs[i]);
                    i++;
                }
            
                if(i >= 20){
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return 0;
                }
                lineargs[i] = NULL;               /* child process */
                if (execvp(lineargs[0], lineargs) == -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    exit(1);
                } 
            break;
            default:              /* parent process */
                continue;
            }
        }
        // https://stackoverflow.com/questions/19461744/how-to-make-parent-wait-for-all-child-processes-to-finish
        while(wait(&status) > 0);
        printf("Child done, status: %d\n", status);
        return 0;
}

int readfile(char *file){
    FILE *fp = fopen(file, "r");

    if(fp == NULL){
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, fp) != -1){
        create_fork(line);
    }
    fclose(fp);
    free(line);
    return 0;
}

int main(int argc, char *argv[]){

    char *line = NULL;
    char *exit ="exit\n";
    size_t size = 0;
    if(argc > 1){
        readfile(argv[1]);
        return 0;
    }
    while(1){
        getline(&line, &size, stdin);
        if(strcmp(line, exit) == 0){
            break;
        }
        create_fork(line);
    }
    return 0;
}

