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
    char *p;
    int sig_number;
    int conv = strtol(argv[1], &p, 10);
    sig_number = conv;
    int n = 2;
    int i;
    int pid = getpid();

    setpgid(0, 0);

    if (signal(sig_number, SIG_IGN) == SIG_ERR)
    {
        perror("Function 'signal' had problem with ignoring signal");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++)
    {
        int id = fork();
        switch (id)
        {
        case -1:
            perror("FORK ERROR");
            exit(1);
        case 0:
            //printf("PGID: %d\n", getpgrp());
            execl("./3A", "3A", "custom", argv[1], NULL);
        default:
            setpgid(id, pid);
            //sleep(2);
            //wait(NULL);
        }
    }
    wait(NULL);
    printf("IGNORING PROGRAM WAITING FOR SIGNAL");
    pause();
    return 0;
}