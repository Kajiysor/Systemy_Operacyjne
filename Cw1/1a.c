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
    printf("| %i | %i | %i | %i | %i |\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
    printf("====================================\n\n");
}

int main()
{
    printf("| UID  | GID  | PID  | PPID | PGID |\n");
    info();
    return 0;
}