#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <semaphore.h>
#include "semaphores_lib.h"

bool using_critical_section;
char semaphore_name[20] = "/my_semaphore";

void exit_function(void)
{
    if (using_critical_section)
    {
        delete_semaphore(semaphore_name);
    }
}

void INT_signal_handler(int signal)
{
    if (using_critical_section == 1)
    {
        delete_semaphore(semaphore_name);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 7)
    {
        printf("Invalid amount of arguments, please provide correct arguments!\n \
        Argumenty to: [0] Nazwa programu [1] Nazwa wywolywanego programu [2] Ilosc inkrementacji \
        [3] Ilosc sekcji krytycznych [4] Nazwa pliku [5] Nazwa semafora [6] Uzywanie sekcji krytycznej");
    }

    if (atexit(exit_function) != 0)
    {
        perror("Atexit error!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, INT_signal_handler) == SIG_ERR)
    {
        perror("Signal handler error!\n");
        exit(EXIT_FAILURE);
    }

    int file, i;
    int increment_amount;

    increment_amount = atoi(argv[2]);

    if (atoi(argv[6]) != 0)
    {
        using_critical_section = true;
    }
    else
    {
        using_critical_section = false;
    }

    if ((file = open("numer.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        perror("Error opening/creating file for writing!\n");
        exit(EXIT_FAILURE);
    }

    if (write(file, "0", 2) == -1)
    {
        perror("Error writing to file!\n");
        exit(EXIT_FAILURE);
    }

    if (close(file) == -1)
    {
        perror("Error closing file!\n");
        exit(EXIT_FAILURE);
    }

    if (using_critical_section)
    {
        sem_t *semaphore = create_semaphore(semaphore_name);
        int sem_value;
        semaphore_value(semaphore, &sem_value);
        printf("Created semaphore: %s [%p] with value of %d\n", semaphore_name, (void *)semaphore, sem_value);
    }

    for (i = 0; i < increment_amount; i++)
    {
        switch (fork())
        {
        case -1:
            perror("Fork error!\n");
            exit(EXIT_FAILURE);

        case 0:
            execl(argv[1], argv[1], argv[3], "numer.txt", argv[5], argv[6], NULL);
            perror("Exec error!\n");
            _exit(EXIT_FAILURE);
            break;

        default:
            break;
        }
    }

    for (i = 0; i < increment_amount; i++)
    {
        wait(NULL);
    }

    if ((file = open("numer.txt", O_RDONLY, 0644)) == -1)
    {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    int reading;
    char buffer[10];

    reading = read(file, &buffer, 10);
    switch (reading)
    {
    case -1:
        printf("Error reading from the file!\n");
        exit(EXIT_FAILURE);

    case 0:
        printf("File is empty!\n");
        exit(EXIT_FAILURE);

    default:
        buffer[reading] = '\0';
        if (atoi(buffer) == (atoi(argv[2]) * atoi(argv[3])))
        {
            printf("Incrementing successfull!\n");
        }
        else
        {
            printf("Incrementing failed!\n");
        }
    }

    if (close(file) == -1)
    {
        perror("Error closing file!\n");
        exit(EXIT_FAILURE);
    }
}
