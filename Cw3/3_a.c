#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void my_signal_handler(int signum)
{
    printf("\nI have been handled!\n");
    sleep(1);
}

void ignoring_handler(int sig_number)
{
    if (signal(sig_number, SIG_IGN) == SIG_ERR)
    {
        perror("Function 'signal' had problem with ignoring SIGINT");
        exit(EXIT_FAILURE);
    }
}

void default_handler(int sig_number)
{
    if (signal(sig_number, SIG_DFL) == SIG_ERR)
    {
        perror("Function 'signal' had problem with handling SIGINT");
        exit(EXIT_FAILURE);
    }
}

void customized_handler(int sig_number)
{
    if (signal(sig_number, my_signal_handler) == SIG_ERR)
    {
        perror("Function 'signal' had problem with handling SIGINT");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    char *p;
    int sig_number;
    int conv = strtol(argv[2], &p, 10);
    sig_number = conv;
    if (argv[1] == NULL)
    {
        printf("You have not specified a signal handler, running default\n");
        //default_handler();
    }
    else
    {
        char *argument = argv[1];

        if (strcmp(argument, "default") == 0)
        {
            //exit(2);
            default_handler(sig_number);
        }

        else if (strcmp(argument, "ignore") == 0)
        {
            //exit(3);
            ignoring_handler(sig_number);
        }

        else if (strcmp(argument, "custom") == 0)
        {
            customized_handler(sig_number);
            // if (signal(sig_number, my_signal_handler) == SIG_ERR)
            // {
            //     perror("Function 'signal' had problem with handling SIGINT");
            //     exit(EXIT_FAILURE);
            // }
        }
        else
        {
            printf("You have provided wrong argument, please put default, ignore or custom as an argument!\n");
            exit(1);
        }
    }

    int PID = getpid();
    printf("PID: %d\n", PID);
    printf("\nI am waiting for a signal\n");
    pause();

    return 0;
}
