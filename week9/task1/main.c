#include "header.h"
#include <stdio.h>

int main(){
	int final_value;
	printf("This program adds two numbers together\n");
	final_value = ask_number();
	printf("The total is %d\n", final_value);
	return 0;
}
