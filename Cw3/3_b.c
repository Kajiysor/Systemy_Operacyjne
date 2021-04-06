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
    int id;
    char *p;
    int sig_number;
    int conv = strtol(argv[2], &p, 10);
    sig_number = conv;

    printf("Main proccess PID: %d\n", getpid());
    switch (id = fork())
    {
    case -1:
        perror("FORK ERROR");
        exit(1);
    case 0:
        sleep(1);
        execl("./test", "test", argv[1], argv[2], NULL);
        perror("exec1 error");
        _exit(2);
    default:
        sleep(2);
        kill(id, 0);
        if (errno == ESRCH)
        {
            printf("Proccess doesn't exist\n");
            exit(3);
        }
        else
        {
            kill(id, sig_number);
        }
        wait(NULL);
    }
    return 0;
}