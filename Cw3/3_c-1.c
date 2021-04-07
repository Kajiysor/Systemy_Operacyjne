#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int sig_number;
    int pgid;

    if (argv[1] != NULL)
    {
        sig_number = atoi(argv[1]);
    }

    if (argv[1] == NULL)
    {
        printf("You have not specified a signal number, please provide the signal number as a second argument!\n");
        exit(2);
    }

    printf("Main proccess PID: %d\n", getpid());
    int id = fork();
    switch (id)
    {
    case -1:
        perror("FORK ERROR");
        exit(1);
    case 0:
        sleep(1);
        execl("./3C-2", "3C-2", argv[1], NULL);
        perror("exec1 error");
        _exit(2);
    default:
        sleep(4);
        pgid = getpgid(id);
        //printf("FROM FIRST PROCESS - variable 'id': %d\n", id);
        //printf("FROM FIRST PROCCESS - PGID TO KILL: %d\n", pgid);
        kill(-pgid, 0);
        if (errno == ESRCH)
        {
            printf("Proccess doesn't exist\n");
            exit(3);
        }
        else
        {
            kill(-pgid, sig_number);
        }
        wait(NULL);
    }
    return 0;
}