#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int create_fork(char *line){
    int status;
    char* ptr = line;
    char* token;
    token = strtok_r(line, "\n", &ptr);
    ptr = token;

    
    while((token = strtok_r(ptr, "&", &ptr))){
        printf("Lineargs: %s\n", token);
        pid_t pid = fork();
        switch (pid) {
            case -1:              /* error in fork */
                perror("fork fail");
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
                    printf("Too many arguments\n");
                    return 0;
                }
                lineargs[i] = NULL;               /* child process */
                if (execvp(lineargs[0], lineargs) == -1) {
                    perror("execvp");
                    exit(1);
                } 
            break;
            default:              /* parent process */
                continue;
            }
        }
        while(wait(&status) > 0);
        printf("Child done, status: %d\n", status);
        return 0;
}

int main(int argc, char *argv[]){

    char *line = NULL;
    char *exit ="exit\n";
    size_t size = 0;
    while(1){
        getline(&line, &size, stdin);
        if(strcmp(line, exit) == 0){
            break;
        }
        create_fork(line);
    }
    return 0;
}

