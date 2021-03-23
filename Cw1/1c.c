#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int i;

    for (i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("FORK ERROR");
            exit(1);
        case 0:
            printf("Child started\n");
            fflush(stdout);
            sleep(5);
            printf("Child stopped\n");
            fflush(stdout);
            printf("Adopted by [%d]\n", getppid());
            fflush(stdout);
        default:
            break;
        }
    }
    return 0;
}