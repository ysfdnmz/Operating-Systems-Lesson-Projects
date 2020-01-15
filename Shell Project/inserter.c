//
//  inserter.c
//  OS_Project
//
//  Created by Yusuf Dönmez on 30.11.2019.
//  Copyright © 2019 Yusuf Dönmez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, const char * argv[],char ** envp)
{
    FILE *fp;
    fp = fopen("database.txt", "w+");
    if ( fp == NULL )
    {
        printf( "database.txt file failed to open." ) ;
    }

    //dosyaya yazma işlemi
    fprintf(fp,"%s",*argv);
    printf("inserted!\n");

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
