#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void info()
{
    printf("====================================\n");
    printf("| %d | %d | %d | %d | %d |\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
    printf("====================================\n\n");
}

int main()
{
    printf("Child Process:\n");
    info();
    return 0;
}