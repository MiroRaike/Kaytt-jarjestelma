#include <stdio.h>

int ask_number(){

	int x, y;
	printf("First number: ");
	scanf("%d", &x);
	printf("Second number: ");
	scanf("%d", &y);
	return (x+y);
}
