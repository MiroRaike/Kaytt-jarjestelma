#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    char *line = NULL;
    size_t size = 0;
    getline(&line, &size, stdin);
    printf("%s", line);
    return 0;
}
