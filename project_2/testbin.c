#include <stdio.h>

int main()
{
   // declaring a file pointer
   FILE *filePointer;

   // initializing a char array which we have to write into the file
   char str[] = "Hello World";

   // opening the file in write mode
   filePointer = fopen("test.txt", "w");

   // using fwrite(), writing the above char array into the specified file
   fwrite(str, 1, sizeof(str) - 1, filePointer);

   // closing the file
   fclose(filePointer);

   return 0;
}
