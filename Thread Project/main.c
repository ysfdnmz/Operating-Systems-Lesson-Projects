#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_mutex_t lockreader;
pthread_mutex_t lockcalculate;

pthread_t readerthread;
pthread_t calculatethread;

int geneltoplam = 0;
char buffer[10];
int calculatorloopcounnter = 1;
int readerloopcounter = 1;
int pipefd[2];
int counterthreadsonlandır = 1;

void *threadCalculator() {

        pthread_mutex_lock(&lockcalculate);

        for (int k = 0; k < sizeof(buffer); ++k) {
            if(buffer[k] == '\n')
            {
                buffer[k] = '\0';
            }
            if(buffer[k] == '\0')
            {
                continue;
            }
            char c = buffer[k];
            int x = c - '0';

            geneltoplam = geneltoplam + x;

        }

        pthread_mutex_unlock(&lockcalculate);
    pthread_mutex_destroy(&lockcalculate);
}

void *threadReader(){

    //pthread_mutex_lock(&lockreader);
   // printf("threadreader çalıştı\n");
       read(pipefd[0], buffer, sizeof(buffer));
       for (int i = 0; i < sizeof(buffer) ; ++i) {
            if(buffer[i] == '-')
            {
                counterthreadsonlandır = 0;
                //exit(1);
            }
            else if(buffer[i] == '\n')
            {
                buffer[i] = '\0';
            }
       }
       sleep(1);
    pthread_mutex_unlock(&lockreader);
       pthread_mutex_destroy(&lockreader);


}

int main(int argc, const char * argv[], char ** envp) {
    memset(buffer, 0, sizeof(buffer));

    pthread_mutex_init(&lockreader, NULL);
    pthread_mutex_init(&lockcalculate, NULL);

    printf("Before Thread\n");

    //pthread_create(&readerthread, NULL, threadReader, NULL);
    //pthread_create(&calculatethread, NULL, threadCalculator, NULL);


    int counter = 1;

    int pid;
    int h;

    if(pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid == 0){
        //Child process
        h = execve("reader", NULL, envp);

    }else{

        while(counterthreadsonlandır > 0)
        {
            pthread_create(&readerthread, NULL, threadReader, NULL);
            pthread_create(&calculatethread, NULL, threadCalculator, NULL);
            printf("Genel Toplam: %d\n", geneltoplam);
            sleep(5);
        }

        void* status;
        pthread_join(readerthread, &status);
        pthread_join(calculatethread, &status);
        wait(&h);

        /*while(1)
{

    read(pipefd[0], buffer, sizeof(buffer));
    pthread_create(&readerthread, NULL, threadReader, NULL);



}
 */
    }




    return 0;
}
