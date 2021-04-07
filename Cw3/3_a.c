#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void my_signal_handler(int sig_number)
{
    extern const char *const sys_siglist[];
    printf("\nI have handled signal number %d - %s!\n", sig_number, sys_siglist[sig_number]);
    sleep(1);
}

void ignoring_handler(int sig_number)
{
    if (signal(sig_number, SIG_IGN) == SIG_ERR)
    {
        perror("Function 'signal' had problem with ignoring signal");
        exit(EXIT_FAILURE);
    }
}

void default_handler(int sig_number)
{
    if (signal(sig_number, SIG_DFL) == SIG_ERR)
    {
        perror("Function 'signal' had problem with handling signal");
        exit(EXIT_FAILURE);
    }
}

void customized_handler(int sig_number)
{
    if (signal(sig_number, my_signal_handler) == SIG_ERR)
    {
        perror("Function 'signal' had problem with handling signal");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    int sig_number;

    if (argv[1] != NULL && argv[2] != NULL)
    {
        sig_number = atoi(argv[2]);
    }
    if (argv[1] == NULL)
    {
        printf("You have not specified a signal handler, running default!\n");
    }
    else if (argv[2] == NULL)
    {
        printf("You have not specified a signal number, please provide the signal number as a second argument!\n");
        exit(2);
    }
    else
    {
        char *argument = argv[1];

        if (strcmp(argument, "default") == 0)
        {
            default_handler(sig_number);
        }

        else if (strcmp(argument, "ignore") == 0)
        {
            ignoring_handler(sig_number);
        }

        else if (strcmp(argument, "custom") == 0)
        {
            customized_handler(sig_number);
        }
        else
        {
            printf("You have provided wrong argument, please put default, ignore or custom as an argument!\n");
            exit(1);
        }
    }

    printf("PID: %d\n", getpid());
    printf("I am waiting for a signal\n");
    pause();

    return 0;
}
