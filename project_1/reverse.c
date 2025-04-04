#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#define	MAX 1000

int main(int argc, char *argv[]) {

	int i=0;
	char buffer[MAX];

	if(argc > 3) {
		fprintf(stderr, "Usage: Input, Output file\n");
		exit(1);
	}
	
	// if no argument given
	if(argc == 1) {

		char **ptr;
		ptr = (char **)malloc(i*sizeof(char *));
		if(ptr == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
		while(fgets(buffer, MAX, stdin) != NULL){
			// if line is empty stop adding to ptr
			if(strcmp(buffer, "\n") == 0) {
				break;
			}
			++i;
			ptr = (char **)realloc(ptr, i*sizeof(char *));
			if(ptr == NULL) {
				fprintf(stderr, "malloc failed\n");
				exit(1);
			}
			ptr[i-1] = (char *)malloc(strlen(buffer)*sizeof(char));
			if(ptr[i-1] == NULL) {
				fprintf(stderr, "malloc failed\n");
				exit(1);
			}
			strcpy(ptr[i-1], buffer);
		}

		fprintf(stdout, "Printing in reverse order\n");

		while(i>0){
			i--;
			fprintf(stdout,"%s", ptr[i]);
		}

		fprintf(stdout, "End of reverse order\n");

		free(ptr);

	}else{

		// Allocating memory and reading file.

		int startOfLine=0;

		int *ptr = (int *)malloc(i*sizeof(int));

		if(ptr == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}

		FILE *file = fopen(argv[1], "r");
		if (file == NULL) {
			perror("Could not open file");
			exit(1);
		}

		// Get where lines start and store them on an array.
		while(fgets(buffer, MAX, file) != NULL){
			++i;
			ptr = (int *)realloc(ptr, i*sizeof(int));
			if(ptr == NULL) {
				fprintf(stderr, "malloc failed\n");
				exit(1);
			}
			ptr[i-1] = startOfLine += strlen(buffer);
		}
		// fseek gets the last line twice which is annoying so have to decrement i by 1 before the call.
		i--;

		// When only one argument is given, print to stdout.
		if(argc == 2) {
			while(i>-1){
				i--;
				fseek(file, ptr[i], SEEK_SET);
				fgets(buffer, sizeof(buffer), file);
				fprintf(stdout,"%s", buffer);
			}
		}

		// When two arguments are given, write to file.
		if(argc == 3) {
			FILE *fileToWrite = fopen(argv[2], "w");

			while(i>-1){
				i--;
				fseek(file, ptr[i], SEEK_SET);
				fgets(buffer, sizeof(buffer), file);
				// https://www.tutorialspoint.com/c_standard_library/c_function_fputs.htm
				if(fputs(buffer, fileToWrite) == EOF){
					fprintf(stderr, "Error writing to file\n");
					fclose(fileToWrite);
					exit(1);
				}
			}

			fclose(fileToWrite);
		}
		free(ptr);
		fclose(file);
	}
	return 0;
}
