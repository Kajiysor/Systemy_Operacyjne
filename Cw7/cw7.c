#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include "shared_memory.h"
#include "semaphores_lib.h"

#define ELEMENTS 20
#define BUFF 5
#define PRODUCER_SEMAPHORE "/producer_semaphore"
#define CONSUMER_SEMAPHORE "/consumer_semaphore"
#define OUTPUT "output"
#define INPUT "input"
#define SHARED_MEMORY_NAME "producer_consumer_shared_memory"

typedef struct
{
    char buffer[BUFF][ELEMENTS];
    int writing;
    int reading;
} Shared_Memory_Section;

void my_sig_handler(int signal)
{
    printf("Interrupt signal, deleting semaphores and shared memory!\n");
    exit(EXIT_SUCCESS);
}

void deleting(void)
{
    delete_shared_memory(SHARED_MEMORY_NAME);
    delete_semaphore(PRODUCER_SEMAPHORE);
    delete_semaphore(CONSUMER_SEMAPHORE);
}

int main(int argc, char *argv[])
{
    int shared_memory_desc;
    sem_t *semaphore;

    if (argc != 3)
    {
        printf("Invalid amount of arguments, please provide producer name and consumer name!\n");
        exit(EXIT_FAILURE);
    }

    semaphore = create_semaphore(PRODUCER_SEMAPHORE, BUFF);
    printf("Created semaphore: %s [%p] with value of %d\n", PRODUCER_SEMAPHORE, (void *)semaphore, semaphore_value(semaphore));
    semaphore = create_semaphore(CONSUMER_SEMAPHORE, 0);
    printf("Created semaphore: %s [%p] with value of %d\n", PRODUCER_SEMAPHORE, (void *)semaphore, semaphore_value(semaphore));

    shared_memory_desc = create_shared_memory(SHARED_MEMORY_NAME);
    set_shared_memory_size(shared_memory_desc, sizeof(Shared_Memory_Section));
    printf("Created shared memory %s with the descriptor %d and size of %ld!\n", SHARED_MEMORY_NAME, shared_memory_desc, sizeof(Shared_Memory_Section));

    if (atexit(deleting) != 0)
    {
        perror("Atexit function error!\n");
        _exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, my_sig_handler) == SIG_ERR)
    {
        perror("Signal error!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < 2; i++)
    {
        switch (fork())
        {
        case -1:
            perror("Fork error!\n");
            exit(EXIT_FAILURE);

        case 0:
            if (i == 0)
            {
                execl(argv[1], argv[1], PRODUCER_SEMAPHORE, CONSUMER_SEMAPHORE, SHARED_MEMORY_NAME, INPUT, NULL);
                perror("Execl function error!\n");
                _exit(EXIT_FAILURE);
            }
            else
            {
                execl(argv[2], argv[2], PRODUCER_SEMAPHORE, CONSUMER_SEMAPHORE, SHARED_MEMORY_NAME, OUTPUT, NULL);
                perror("Execl function error!\n");
                _exit(EXIT_FAILURE);
            }
            break;

        default:
            break;
        }
    }

    for (int j = 0; j < 2; j++)
    {
        wait(NULL);
    }

    close_shared_memory(shared_memory_desc);

    return 0;
}
