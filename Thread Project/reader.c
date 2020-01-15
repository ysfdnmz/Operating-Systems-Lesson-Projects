//
// Created by Yusuf Dönmez on 14.12.2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

#define MAXCHAR 1000

int main(int argc, const char * argv[],char ** envp) {
    //int pipefd[2];
    char str[10];
    char pushed_str[MAXCHAR];
    char backup_str[MAXCHAR];
    int while_counter = 1;

    memset(str, 0, sizeof(str));
    printf("reader çalıştı\n");

    while(while_counter > 0) {
        FILE *fp;
        fp = fopen("data.txt", "r");
        if (fp == NULL) {
            printf("database.txt file failed to open.");
        }

        while (fgets(str, MAXCHAR, fp) != NULL) {
            for (int k = 0; k <sizeof(str) ; ++k) {
                if (str[k] == '-') {
                    while_counter = 0;
                }
            }

            write(4 , str, sizeof(str));
            if(while_counter > 0){

            }

        }
        fclose(fp);

    }

    return 0;
}
