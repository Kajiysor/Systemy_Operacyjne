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
    //int forks[3];
    int id;

    printf("Parent Process:\n");
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
            info();
            fflush(stdout);
            sleep(4 - i);
        default:
            sleep(8);
        }
    }

    /*for (i = 0; i < 3; i++)
    {
        forks[i] = fork();
    }

    if (forks[0] != 0 && forks[1] != 0 && forks[2] != 0)
    {
        printf("Macierzysty\n");
        info();
        sleep(30);
    }
    else if (forks[0] == 0 && forks[1] != 0 && forks[2] != 0)
    {
        sleep(3);
        printf(" %i | %i | %i | %i  | %i \n\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
        sleep(3);
    }
    else if (forks[1] == 0 && forks[2] != 0)
    {
        sleep(3);
        printf(" %i | %i | %i | %i  | %i \n\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
        sleep(8);
    }
    else if (forks[2] == 0)
    {
        sleep(5);
        printf(" %i | %i | %i | %i  | %i \n\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
        sleep(13);
    }*/
    return 0;
}