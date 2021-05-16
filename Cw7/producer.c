#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "shared_memory.h"
#include "semaphores_lib.h"

#define ELEMENTS 10
#define BUFF 5

typedef struct
{
    char buffer[BUFF][ELEMENTS];
    int writing;
    int reading;
} Shared_Memory_Section;

int main(int argc, char *argv[])
{
    int file, shared_memory_desc, reading;
    sem_t *producer_semaphore;
    sem_t *consumer_semaphore;
    Shared_Memory_Section *SharedMemory;

    if (argc != 5)
    {
        printf("Producer Error!\n");
        printf("Invalid amount of arguments, please provide producer semaphore name, consumer semaphore name, shared memory name and input file!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    if ((file = open(argv[4], O_RDONLY, 0644)) == -1)
    {
        printf("Error opening file for reading!\n");
        exit(EXIT_FAILURE);
    }

    producer_semaphore = open_semaphore(argv[1]);
    printf("PRODUCER -- Opened producer semaphore %s  [%p]\n", argv[1], (void *)producer_semaphore);
    consumer_semaphore = open_semaphore(argv[2]);
    printf("CONSUMER -- Opened consumer semaphore %s  [%p]\n", argv[2], (void *)consumer_semaphore);

    shared_memory_desc = open_shared_memory(argv[3]);
    printf("PRODUCER -- Opened shared memory %s  [%d]\n", argv[3], shared_memory_desc);

    SharedMemory = (Shared_Memory_Section *)map_shared_memory(shared_memory_desc, sizeof(Shared_Memory_Section));

    while (1)
    {
        sleep(rand() % 3 + 1);
        printf("PRODUCER -- Before Critical Section [Semaphore]: %d\n", semaphore_value(producer_semaphore));
        semaphore_P(producer_semaphore);

        /* CRITICAL SECTION */
        reading = read(file, SharedMemory->buffer[SharedMemory->writing], ELEMENTS);
        if (reading == -1)
        {
            printf("Error reading from file!\n");
            exit(EXIT_FAILURE);
        }
        if (reading != ELEMENTS)
        {
            SharedMemory->buffer[SharedMemory->writing][reading] = '\0';
            printf(">>>> Producing ----> (%ld): %s\n", strlen(SharedMemory->buffer[SharedMemory->writing]), SharedMemory->buffer[SharedMemory->writing]);
            printf("PRODUCER -- End of File\n");

            semaphore_V(consumer_semaphore);
            printf("PRODUCER -- After Critical Section [Semaphore]: %d\n", semaphore_value(consumer_semaphore));
            break;
        }
        else
        {
            printf(">>>> Producing ----> (10): %.10s\n", SharedMemory->buffer[SharedMemory->writing]);
            printf(">>>> Buffer index writing: %d\n", SharedMemory->writing);
        }

        SharedMemory->writing = (SharedMemory->writing + 1) % BUFF;

        semaphore_V(consumer_semaphore);
        printf("PRODUCER -- After Critical Section [Semaphore]: %d\n", semaphore_value(consumer_semaphore));
    }

    if (close(file) == -1)
    {
        perror("Error closing file!\n");
        exit(EXIT_FAILURE);
    }

    delete_shared_memory_mapping(SharedMemory, sizeof(Shared_Memory_Section));
    close_shared_memory(shared_memory_desc);

    printf("PRODUCER -- End of Process\n");

    return 0;
}