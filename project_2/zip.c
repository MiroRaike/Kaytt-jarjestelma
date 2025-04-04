#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("my-zip: searchterm [file ...]\n");
        exit(1);
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("File not found\n");
        exit(1);
    }

    FILE *compressed;

    compressed = fopen(argv[2], "wb");

    int ch;
    int last_ch = 0;
    int count = 0;

    while ((ch = fgetc(fp)) != EOF){
        if(last_ch == 0){;
            last_ch = ch;
        }
        if(ch != last_ch){
            fwrite(&count, sizeof(int), 1, compressed);
            fwrite(&last_ch, 1, 1, compressed);
            count = 0;
        }

        last_ch = ch;
        count += 1;
        /*if(ch == '\n'){
            printf("New line pog\n");
            last_ch = NULL;
            fwrite("\n", 1, 1, compressed);
            count = 0;
            continue;
        }*/


            /*printf("%d ", ch);
            printf("%d\n", count);
            int i=0;
            int binaryNumber[32] ={0};
            int binaryChar[8] = {0};
        
            // Bit weird but this way don't have to put if in for or while.
            while(last_ch > 0){
                binaryChar[i] = last_ch % 2;
                last_ch = last_ch / 2;
                ++i; 
            }

            i=0;
            while(count > 0){
                binaryNumber[i] = count % 2;
                count = count / 2;
                ++i; 
            }

            for(i=31;i >-1; i--){
                // kind of weird way to get it into the desired format
                printf("%d", binaryNumber[i]);
                fwrite(binaryNumber[i], sizeof binaryNumber[i], 1, compressed);
            }
            printf(" ");
            for(i=7;i > -1; i--){
                printf("%d", binaryNumber[i]);
                fwrite(binaryChar[i], sizeof binaryChar[i], 1, compressed);
            }*/
    }
    printf("Finished writing zip\n");
    fclose(fp);
    fclose(compressed);
    return 0;
}