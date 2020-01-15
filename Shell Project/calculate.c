//
//  calculate.c
//  OS_Project
//
//  Created by Yusuf Dönmez on 30.11.2019.
//  Copyright © 2019 Yusuf Dönmez. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXCHAR 1000

int main(int argc, const char * argv[],char ** envp)
{
    FILE *fp;
    char ch;
    char myarray[80];
    char readarray[100];

    fp = fopen("database.txt", "r+");
    if ( fp == NULL )
    {
        printf( "database.txt file failed to open." ) ;
    }

    // argv ** char yapısı bu yüzden onu char * bir diziye concat işlemi yapıyorum.
    strcat(myarray,argv[0]);

    if(myarray[1] == 's')
    {
        //dosya okunuyor
        while(fgets(readarray, MAXCHAR, fp) != NULL);

        //bu bölümde char dizi okunduğu için bu char elemanların int dönüşümü gerçekleştirilmiştir.
        int intarray[100];
        memset(intarray, 0, sizeof intarray);
        int count = 0;
        int count2 = 0;
        int count3 = 0;
        char temparray[100];
        while(readarray[count] != '\0'){
            temparray[count2] = readarray[count];
            count2++;
            if(readarray[count] == ' ')
            {
                int i = 0;
                sscanf(temparray, "%d", &i);
                memset(temparray, 0, sizeof temparray);
                intarray[count3] = i;
                count3++;
                count2 = 0;
            }
            count++;
        }

        //bu dosyaya gönderdiğim parametrede yapı gereği '-' 0. 's' 1. ' '2. 'gönderilen ilk sayı' 3. elemanda olduğu için onun char değerini int'e çeviriyorum.
        char c = myarray[3];
        int x = c - '0';

        // aynı şekilde 2. sayı 5. dizi elemanında
        char c2 = myarray[5];
        int x2 = c2 - '0';

        //artık int array'im var istediğim indeksi alabilirim. istediğim indeksleri s_resultta topluyorum
        int s_result = intarray[x] + intarray[x2];

        printf("%d\n",s_result);


    }

    if(myarray[1] == 'r')
    {
        //dosya okunuyor
        while(fgets(readarray, MAXCHAR, fp) != NULL);


        //bu bölümde char dizi okunduğu için bu char elemanların int dönüşümü gerçekleştirilmiştir.
        int intarray[100];
        memset(intarray, 0, sizeof intarray);
        int count = 0;
        int count2 = 0;
        int count3 = 0;
        char temparray[100];
        while(readarray[count] != '\0'){
            temparray[count2] = readarray[count];
            count2++;
            if(readarray[count] == ' ')
            {
                int i = 0;
                sscanf(temparray, "%d", &i);
                memset(temparray, 0, sizeof temparray);
                intarray[count3] = i;
                count3++;
                count2 = 0;
            }
            count++;
        }

        char c = myarray[3];
        int x = c - '0';

        char c2 = myarray[5];
        int x2 = c2 - '0';

        //artık int array'im var istediğim indeksi alabilirim. istediğim indeksleri r_resultta topluyorum
        int r_result = 0;

        // kullanıcı 2 ile 4 arasında sayıları isteyebileceği gibi 4 ile 2 arasındaki sayıları da isteyebilir. bu kontrolleri yapıyorum.
        if(x > x2)
        {
            for (int p = x2+1; p < x; p++) {
                r_result = intarray[p] + r_result;
            }
        }
        if(x2 > x){
            for (int o = x+1; o < x2; o++) {
                r_result = intarray[o] + r_result;
            }
        }

        printf("%d\n",r_result);

    }

    //dosya kapatma
    fclose(fp);

    //ana programa tekrar fork işlemi
    int newfork;
    newfork = fork();
    if(newfork!=0)
    {
        int newexec;
        newexec = execve("./accountant", NULL, envp);
    }
    else
    {
        exit(0);
    }



    return 0;
}
