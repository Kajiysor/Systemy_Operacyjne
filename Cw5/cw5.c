#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

const char *pointer;

const char *manufacturer = "MANUFACTURER";
const char *consumer = "CONSUMER";

void deleting_fifo(){
    if (unlink(pointer) != 0){
        printf ("Error deleting fifo\n");
        exit(1);
    }
}

void sig_handler(){
    if (signal(SIGINT, deleting_fifo) == SIG_ERR){
        printf("Error handling SIG_INT");
        exit(EXIT_FAILURE);
    }
}

int main( int argc, char *argv[] ){
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL){
            printf("Please provide the source file as the first argument, output file as a second argument and FIFO name as the third argument!\n");
            exit(10);
        }

    pointer = argv[3];

     if (atexit(deleting_fifo) != 0){
         printf("ATEXIT ERROR!\n");
         exit(EXIT_FAILURE);
     }

    if (mkfifo(argv[3], 0664) == -1){
        printf("ERROR WHILE MAKNG A FIFO!\n");
        exit(EXIT_FAILURE);
    }

    int id, i, j;
    int n = 2;
    printf("Running fork for loop\n");
    for(i = 0; i<n; i++)
    {
        id = fork();
        switch(id)
        {
            case -1:
                printf("Fork error");
                exit(2);

            case 0:
                if (i == 0){
                    printf("RUNNING MANUFACTURER\n");
                    execl(manufacturer, manufacturer, argv[1], argv[2], argv[3], NULL);
                    perror("execl error");
                    _exit(3);
                }
                if (i == 1){
                    printf("RUNNING CONSUMER\n");
                    execl(consumer, consumer, argv[1], argv[2], argv[3], NULL);
                    perror("execl error");
                    _exit(4);
                }

            default:
            printf("\n");
        }
    }    
    for(j = 0; j<2; j++){
        wait(NULL);
    }
}