#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int create_fork(char *line){
    int status;
    char *lineargs[20];
    char* ptr = line;
    char* token;
    int i = 0;

    // Removing new line, not very pretty looking
   token = strtok_r(line, "\n", &ptr);
   ptr = token;

   char *test[] = {"ls", "-l", NULL, "test", NULL};

   printf("Lineargs: %s\n", lineargs[0]);
   pid_t pid = fork();
   switch (pid) {
      case -1:              /* error in fork */
         perror("fork fail");
         exit(1);
      case 0:
         while((token = strtok_r(ptr, " ", &ptr))){
            printf("Looping\n");
            lineargs[i] = token;
            printf("Lineargs: %s\n", lineargs[i]);
            i++;
         }
      
         if(i >= 20){
            printf("Too many arguments\n");
            return 0;
         }
         lineargs[i] = NULL;               /* child process */
         printf("Child %d was born, running child...\n", pid);
         if (execvp(lineargs[0], lineargs) == -1) {
            perror("execvp");
            exit(1);
         }           
         break;
      default:              /* parent process */
         printf("Child %d was born, waiting in parent...\n", pid);
         if (wait(&status) == -1) {
            perror("wait");
            exit(1);           }
         printf("Child done, status: %d\n", status);
         break;
   }
   return 0;
}

int splitCommands(char *line){
   
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

