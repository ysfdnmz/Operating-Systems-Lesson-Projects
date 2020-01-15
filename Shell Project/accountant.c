//
//  accountant.c
//  OS_Project
//
//  Created by Yusuf Dönmez on 29.11.2019.
//  Copyright © 2019 Yusuf Dönmez. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_NAME_SZ 256

void append(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

int main(int argc, const char * argv[],char ** envp) {
    // insert code here...

    char str_input[50];
    char storeddata[100];
    char* sending_argv[30];
    char temp_argv[50];
    char temp_argv2[50];
    char* sending_argv2[40];
    memset(storeddata, 0, sizeof storeddata);
    memset(str_input, 0, sizeof str_input);
    memset(sending_argv, 0, sizeof sending_argv);
    memset(temp_argv, 0, sizeof temp_argv);
    memset(temp_argv2, 0, sizeof temp_argv2);
    memset(sending_argv2, 0, sizeof sending_argv2);


    bool flag = true;

    //program hiç kapanmasın diye sonsuz bir while döngüsü
    while(1)
    {
        printf("accountant >>");

        //kullanıcıdan input bekleniyor
        fgets(str_input, MAX_NAME_SZ, stdin);

        //input içinde insert varsa bu if bloğu içine giriliyor
        if (strstr(str_input, "insert") != NULL) {
            int f;
            int i;
            int count = 0;
            int location=0;
            f = fork();
            if(f!=0)
            {
                //insert kelimesini verilen parametrelerden ayrılıyor ve insert programına sadece parametreler gönderiliyor.
                for (int j = 0; j<50; j++) {
                    if( isblank(str_input[j]) )
                    {
                        location = j+1;
                        break;
                    }
                }

                while(str_input[location] != '\0'){
                    temp_argv[count] = str_input[location];
                    location++;
                    count++;
                }
                sending_argv[0] = temp_argv;


                i = execve("./inserter", sending_argv, envp);

                perror("exec: execve hata\n");
                printf("%d",i);

            }
            else{
                exit(0);
            }
        }

        if (strstr(str_input, "calculate") != NULL) {
            int fr;
            int h;
            int location2=0;
            int count2=0;

            fr = fork();
            if(fr!=0)
            {
                // buradaki tek fark calculate ten sonra yazılan -r ve  -s de calculate fork programına gönderiliyor.
                for (int j = 0; j<50; j++) {
                    if( isblank(str_input[j]) )
                    {
                        location2 = j+1;
                        break;
                    }
                }

                while(str_input[location2] != '\0'){
                    temp_argv2[count2] = str_input[location2];
                    location2++;
                    count2++;
                }
                sending_argv2[0] = temp_argv2;

                h = execve("./calc", sending_argv2, envp);

            }
            else{
                exit(0);
            }
        }

        if (strstr(str_input, "readall") != NULL) {
            char ch;
            FILE *fp;
            fp = fopen("database.txt", "r");

            ch = fgetc(fp);
            while (ch != EOF)
            {
                append(storeddata,ch);
                ch = fgetc(fp);
            }
            fclose(fp);
            printf("%s\n",storeddata);
            continue;
        }

        //ekran temizleme
        if (strstr(str_input, "clear") != NULL) {
            for (int s = 0; s <50 ; ++s) {
                printf("\n");
            }
            continue;
        }

        //while döngüsü kırılıp program bitiriliyor.
        if (strstr(str_input, "exit") != NULL) {
            break;
        }

        printf("HATA: Shell'de olmayan bir komut girdiniz.\n");
    }

}
