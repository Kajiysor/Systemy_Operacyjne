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
    int n = 3;
    char *program = argv[1];

    if (argv[1] == NULL)
    {
        printf("ERROR RUNNING THE PROGRAM >> NO ARGUMENT GIVEN:\n");
        printf("Please enter the name of the program that you want to execute, as an argument!\n");
        exit(1);
    }

    printf("Parent Process:\n");
    printf("| UID  | GID  | PID  | PPID | PGID |\n");
    info();
    for (i = 0; i < n; i++)
    {
        switch (fork())
        {
        case -1:
            perror("FORK ERROR");
            exit(1);
        case 0:
            sleep(1);
            execl(program, program, NULL);
            perror("exec1 error");
            _exit(2);
        default:
            wait(NULL);
        }
    }
    return 0;
}