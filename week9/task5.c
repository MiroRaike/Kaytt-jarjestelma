#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define MAXPATH 256

int list_dir(char * dir, int rec)
{
	DIR * dirp;
	char path[MAXPATH];
	struct dirent * direntp;
	struct stat st;
	
	/* Here you should open the directory indicated by the given path */
	/* check functions opendir */
	printf("Opening file\n");

	dirp = opendir(dir);

	printf("Opendir called\n");

	if(dirp == NULL)
	{
		printf("Failed to open directory");
		return 0;
	}
	
	/* Then you should write a loop that reads the directory and prints the 
	   information about the included files */
	/* check function readdir and stat */

	while ((direntp = readdir(dirp)) != NULL ){
		// Seemingly the only way to distinguish hidden files. Although now that if you make "." files yourself
		// The program will not find them.
		if(!(direntp->d_name[0] != '.')){
			continue;
		}
		
		printf("%s\n", direntp->d_name);

		// https://linux.die.net/man/2/stat stat example 
		if(stat(direntp->d_name, &st) == -1) {
			perror("stat");
			exit(EXIT_FAILURE);
		}

		printf("Mode:                     %lo (octal)\n", (unsigned long) st.st_mode);
		printf("Link count:               %ld\n", (long) st.st_nlink);
		printf("File size:                %lld bytes\n", (long long) st.st_size);
		printf("Last file modification:   %s", ctime(&st.st_mtime));

		if((st.st_mode & S_IFMT) == S_IFDIR){
			list_dir(direntp->d_name, (rec+1));
			continue;
		}
	}

	/* Note the recursion, that is, if rec>0 you should recursively call this 
	   function "list_dir" for subdirectories */

	/* You can use the rec-variable to keep track of the recursion depth
	   and also print it with the file listing */

	/* Make sure you handle directories . and .. correctly 
	   (don't list them recursively, or... What happens??) */

	
	/* closing is already given here, but remember to do it yourself in the future :) */
	if (closedir(dirp) == -1) {
		perror(dir);
		return -1;
	}
	
	return 0;
}

int main(int argc, char * * argv)
{
	int i = 1, rec = 0;
	
	if (argc > 1) {
		if (strcmp(argv[i], "-r") == 0) {
			rec = 1;
			i++;
		}
	}
		
	while (i < argc) {
		if (list_dir(argv[i], rec) == -1) exit(1);
		i++;
	}
		
	return 0;
}

