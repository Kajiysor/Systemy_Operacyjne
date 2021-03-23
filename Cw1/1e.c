#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void info()
{
    printf("====================================\n");
    printf("| %d | %d | %d | %d | %d |\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
    printf("====================================\n\n");
}

int main(int argc, char *argv[])
{

    int i;
    int id;

    printf("Parent Process::\n");
    printf("| UID  | GID  | PID  | PPID | PGID |\n");
    info();

    for (i = 0; i < 3; i++)
    {
        id = fork();
        switch (id)
        {
        case -1:
            perror("FORK ERROR");
            exit(1);
        case 0:
            printf("Child Process:\n");
            info();
        default:
            wait(NULL);
            setpgid(id, getpid());
        }
    }
    return 0;
}