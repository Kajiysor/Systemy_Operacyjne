#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
#include "semaphores_lib.h"

int main(int argc, char *argv[])
{

    if (argc != 5)
    {
        printf("Invalid amount of arguments, please provide correct arguments!\n \
        [0] nazwa_programu [1] ilosc_sekcji_krytycznych [2] plik_we_wy [3] nazwa_semafora [4] synchronizacja");
    }

    int reading, number, critical_section_amount, sem_value, file, i;
    char buffer[100];
    char message[200];
    //char semaphore_name[13] = "/my_semaphore";
    bool using_critical_section;
    sem_t *semaphore;

    critical_section_amount = atoi(argv[1]);
    if (atoi(argv[4]) != 0)
    {
        using_critical_section = true;
    }
    else
    {
        using_critical_section = false;
    }

    if (using_critical_section)
    {
        semaphore = open_semaphore(argv[3]);
    }

    for (i = 0; i < critical_section_amount; i++)
    {
        srand(time(NULL));
        sleep(rand() % 5 + 1);

        if (using_critical_section)
        {
            semaphore_value(semaphore, &sem_value);
            printf("[PID]: %d before Critical Section [Semaphore]: %d\n", getpid(), sem_value);
            semaphore_P(semaphore);
        }

        /* CRITICAL SECTION STARTED */

        if ((file = open(argv[2], O_RDONLY, 0644)) == -1)
        {
            perror("Error opening file for reading!\n");
            _exit(EXIT_FAILURE);
        }

        reading = read(file, &buffer, 10);

        switch (reading)
        {
        case -1:
            printf("Error reading from the file!\n");
            _exit(EXIT_FAILURE);

        case 0:
            break;

        default:
            buffer[reading] = '\0';
            semaphore_value(semaphore, &sem_value);
            sprintf(message, ">>>> [PID]: %d [Semaphore]: %d [Number read]: %s [Critical Section Number]: %d", getpid(), sem_value, buffer, i + 1);
            printf("%s\n", message);
        }

        if (close(file) == -1)
        {
            perror("Error closing the file!\n");
            _exit(EXIT_FAILURE);
        }

        number = atoi(buffer);
        number++;
        sprintf(buffer, "%d", number);

        sleep(rand() % 5 + 1);

        if ((file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        {
            perror("Error opening file for writing!\n");
            _exit(EXIT_FAILURE);
        }

        if (write(file, &buffer, strlen(buffer)) == -1)
        {
            perror("Error writing to the file!\n");
            _exit(EXIT_FAILURE);
        }

        if (close(file) == -1)
        {
            perror("Error closing the file!\n");
            _exit(EXIT_FAILURE);
        }

        if (using_critical_section)
        {
            semaphore_V(semaphore);
            semaphore_value(semaphore, &sem_value);
            printf("[PID]: %d after Critical Section [Semaphore]: %d\n", getpid(), sem_value);
        }
    }

    if (using_critical_section)
    {
        close_semaphore(semaphore);
    }
}