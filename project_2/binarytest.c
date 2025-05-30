#include <stdio.h>

int main() {
   FILE *fp;
   int arr[] = {1, 2, 3, 4, 5};
   size_t n = sizeof(arr) / sizeof(arr[0]);

   fp = fopen("example1.bin", "wb");
   if (fp == NULL) {
      perror("Error opening file");
      return 1;
   }

   size_t written = fwrite(arr, sizeof(int), n, fp);
   printf("Number of elements written: %zu\n", written);

   fclose(fp);
   return 0;
}
