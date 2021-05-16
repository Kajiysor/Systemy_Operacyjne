#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int create_shared_memory(const char *name)
{
    int desc = shm_open(name, O_EXCL | O_RDWR | O_CREAT, 0644);
    if (desc == -1)
    {
        perror("Error creating shared memory!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return desc;
    }
}

void delete_shared_memory(const char *name)
{
    if (shm_unlink(name) == -1)
    {
        perror("Error deleting shared memory!\n");
        exit(EXIT_FAILURE);
    }
}

int open_shared_memory(const char *name)
{
    int desc = shm_open(name, O_RDWR, 0644);
    if (desc == 1)
    {
        perror("Error opening shared memory!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return desc;
    }
}

void close_shared_memory(int fd)
{
    if (close(fd) == -1)
    {
        perror("Error closing shared memory!\n");
        exit(EXIT_FAILURE);
    }
}

void set_shared_memory_size(int fd, off_t length)
{
    if (ftruncate(fd, length) == -1)
    {
        perror("Error initializing shared memory!\n");
        exit(EXIT_FAILURE);
    }
}

void *map_shared_memory(int fd, size_t length)
{
    void *adress = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (adress == MAP_FAILED)
    {
        perror("Error mapping shared memory!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return adress;
    }
}

void delete_shared_memory_mapping(void *addr, size_t length)
{
    if (munmap(addr, length) == -1)
    {
        perror("Error deleting shared memory mapping!\n");
        exit(EXIT_FAILURE);
    }
}