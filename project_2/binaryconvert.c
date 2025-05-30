#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int number = 101;
    int i=0;
    int state = 0;

    int binaryNumber[32] ={0};
    int binaryChar[8] = {0};

    // Bit weird but this way don't have to put if in for or while.
    while(number > 0){
        printf("%d ", number % 2 );
        binaryNumber[i] = number % 2;
        number = number / 2;
        printf("Bin %d ", binaryNumber[i]);
        printf("Number %d \n", number);
        printf("%d",i);
        ++i; 
    }
    printf("%d\n", binaryNumber[31]);
    for(i=31;i >-1; i--){
        printf("%d", binaryNumber[i]);
    }
    for(i=7;i > 0; --i){
        fprintf(stdout,"%d\n", binaryNumber[i]);
    }

    printf("State is %d\n",state);

    return 0;
}