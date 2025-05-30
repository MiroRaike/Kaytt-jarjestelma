#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char error_message[30] = "An error has occurred\n";

int create_fork(char *line, int pathAmount, char **paths){
    int status;
    char* ptr = line;
    char* token;
    // First we remove the new line character
    // execvp just does not work if it's included
    token = strtok_r(line, "\n", &ptr);
    ptr = token;

    // Here we split the line into parrael commands and fork them at the same time.
    while((token = strtok_r(ptr, "&", &ptr))){
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
            
                access("bin/ls", X_OK);
                token2 = strtok_r(ptr, " ", &ptr);

                char directory[200];

                char workingPath[300];

                sprintf(workingPath, "%s/%s", getcwd(directory, 200), token2);

                // first check if the current director has the executable
                int foundPath = access(workingPath, X_OK);


                // Messy way to check if the program can be executed or not
                if(foundPath == -1){
                    for(int j = 0; j < pathAmount; j++){
                        sprintf(workingPath, "%s/%s", paths[j], token2);
                        foundPath = access(workingPath, X_OK);
                        if(foundPath != -1){
                            break;
                        }
                    }
                    if(foundPath == -1){
                        printf("No executables found\n");
                        exit(1);
                    }
                }else{
                    sprintf(workingPath, "%s/%s", getcwd(directory, 200), token2);
                }

                // Adding the commands on a list so they work with execv
                lineargs[i] = token2;
                i++;
                while((token2 = strtok_r(ptr, " ", &ptr))){
                    lineargs[i] = token2;
                    i++;
                }
            
                if(i >= 20){
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return 0;
                }
                // last elemennt of the array needs a NULL for some reason
                lineargs[i] = NULL;               /* child process */
                if(execv(workingPath, lineargs) == -1) {
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
        //create_fork(line);
    }
    fclose(fp);
    free(line);
    return 0;
}

int main(int argc, char *argv[]){

    char *line = NULL;
    char *exitString ="exit\n";
    char **paths;
    paths = (char **)malloc(1*sizeof(char *));
    paths[0] = (char *)malloc(strlen("/bin")*sizeof(char));
    strcpy(paths[0], "/bin");
    printf("%s\n", paths[0]);
    char *token;
    size_t size = 0;

    int pathAmount = 1;

    if(argc > 1){
        readfile(argv[1]);
        return 0;
    }
    char directory[200];
    while(1){
        // Too lazy to implement manual relocation, 200 for directory should be enough
        // https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
        printf("%s/ ", getcwd(directory, 200));
        getline(&line, &size, stdin);

        if(strcmp(line, "\n") == 0){
            // Nothing happens if nothing is inputted, otherwise segementation fault will happen trying to split the line
            continue;
        }    

        if(strcmp(line, exitString) == 0){
            break;
        }
        // Need to dupe to use strtok while keeping the original string intact
        char* ptr = strdup(line);
        token = strtok_r(ptr, " ", &ptr);
        if(strcmp(token, "cd") == 0){
            token = strtok_r(ptr, " ", &ptr);
            if(token == NULL){
                printf("No directory given\n");
                continue;
            }
            char *newCD = strdup(token);
            token = strtok_r(ptr, " ", &ptr);
            if(token != NULL){
                printf("Too many arguments given\n");
                continue;
            }
            // Pretty messy way of doing this, need to remove new line from the string for it to correctly assign directorys.
            char* removingNewline;
            removingNewline = strtok_r(newCD, "\n", &newCD);
            if(chdir(removingNewline) != 0){
                printf("Error changing directory\n");
            };
            continue;
        }
        if(strcmp(token, "path") == 0){
            pathAmount = 0;
            printf("Setting paths\n");
            // Allocating memory for paths with realloc and malloc
            while((token = strtok_r(ptr, " ", &ptr))){
                ++pathAmount;
                paths = (char **)realloc(paths, pathAmount*sizeof(char *));
                if(paths == NULL) {
                    fprintf(stderr, "malloc failed\n");
                    exit(1);
                }
                paths[pathAmount-1] = (char *)malloc(strlen(token)*sizeof(char));
                if(paths[pathAmount-1] == NULL) {
                    fprintf(stderr, "malloc failed\n");
                    exit(1);
                }
                strcpy(paths[pathAmount-1], token);
            };
            continue;
        }

        create_fork(line,pathAmount, paths);
    }
    free(paths);
    return 0;
}

