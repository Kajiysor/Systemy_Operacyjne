#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

sem_t *create_semaphore(const char *name)
{
    sem_t *semaphore_adress;
    if ((semaphore_adress = sem_open(name, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
    {
        perror("Error creating semaphore!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return semaphore_adress;
    }
}

sem_t *open_semaphore(const char *name)
{
    sem_t *semaphore_adress;
    if ((semaphore_adress = sem_open(name, 0)) == SEM_FAILED)
    {
        perror("Error opening semaphore!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return semaphore_adress;
    }
}

void close_semaphore(sem_t *sem_t)
{
    if (sem_close(sem_t) == -1)
    {
        perror("Error closing semaphore!\n");
        exit(EXIT_FAILURE);
    }
}

void delete_semaphore(const char *name)
{
    if (sem_unlink(name) == -1)
    {
        perror("Error deleting semaphore!\n");
        exit(EXIT_FAILURE);
    }
}

void semaphore_V(sem_t *sem)
{
    if (sem_post(sem) == -1)
    {
        perror("Error posting semaphore!\n");
        exit(EXIT_FAILURE);
    }
}

void semaphore_P(sem_t *sem)
{
    if (sem_wait(sem) == -1)
    {
        perror("Error waiting semaphore!\n");
        exit(EXIT_FAILURE);
    }
}

void semaphore_value(sem_t *sem, int *sval)
{
    if (sem_getvalue(sem, sval) == -1)
    {
        perror("Error getting semaphore value!\n");
        exit(EXIT_FAILURE);
    }
}