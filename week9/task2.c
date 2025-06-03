#include <stdio.h>
#include <stdlib.h>

// https://stackoverflow.com/questions/31906192/how-to-use-environment-variable-in-a-c-program

int main(int argc, char* argv[])
{
	const char* path = getenv("PATH");
	printf("Environment variable is = %s\n",path);
	
	
	for (int i=0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	printf("\n");
}
