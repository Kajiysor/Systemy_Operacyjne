#define _REENTRANT
#define MAX_THREADS 10
#define MARGIN 4
#define INDENT 45

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "threads.h"

pthread_mutex_t mutex;
pthread_t threads[MAX_THREADS];
int number;
unsigned int threads_amount;
unsigned int section_amount;

void goto_xy(unsigned x, unsigned y)
{
    printf("\033[%d;%dH\033[2K", y, x);
}

void *thread_initialize(void *argument)
{
    int counter = 0;
    int thread_num = *(int *)argument;
    srand(time(NULL));

    printf("Thread => [%d], ID => [%ld]\n", thread_num + 1, threads[thread_num]);

    sleep(1);

    for (int i = 0; i < section_amount; i++)
    {
        goto_xy(0, MARGIN + threads_amount + thread_num);
        printf("\033[35mThread => [%d], Private => [%d], Number => %d \033[0m\n", thread_num + 1, i + 1, number);

        sleep(rand() % 3 + 1);

        //START OF CRITICAL SECTION
        mutex_close(&mutex);

        goto_xy(INDENT, 4 + threads_amount + thread_num);
        printf("\033[1;36mThread => [%d], Critical => [%d], Number => %d \033[0m\n", thread_num + 1, i + 1, number);

        counter = number;
        counter++;

        sleep(rand() % 3 + 1);

        number = counter;

        //END OF CRITICAL SECTION
        mutex_open(&mutex);

        goto_xy(0, MARGIN + threads_amount + thread_num);
        printf("\033[35mThread => [%d], Private => [%d], Number => %d \033[0m\n", thread_num + 1, i + 1, number);

    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Error - wrong amount of arguments!\n");
        printf("Please enter amount of threads and amount of sections!\n");
        exit(EXIT_FAILURE);
    }
    
    threads_amount = atoi(argv[1]);
    if (threads_amount > MAX_THREADS)
    {
        printf("You've exceeded the limit of threads!\n \
        Maximum amount of threads is: %d\n", MAX_THREADS);
        exit(EXIT_FAILURE);
    }
    section_amount = atoi(argv[2]);

    mutex_init(&mutex);
    printf("Initialized mutex => Adress [%p]\n", (void *)&mutex);

    number = 0;

    for (int i = 0; i < threads_amount; i++)
    {
        int *memory = malloc(sizeof(int));
        *memory = i;

        sleep((double)i / threads_amount);
        threads[i] = thread_create(thread_initialize, (void *)memory);
    }

    for (int i = 0; i < threads_amount; i++)
    {
        thread_join(threads[i]);
    }

    goto_xy(0, MARGIN + threads_amount * 2);

    printf("\n==============================\n");

    if (number != threads_amount * section_amount)
    {
        printf("Synchronization failed!\nExpected => %d\nReceived => %d\n", (threads_amount * section_amount), number);
    }
    else
    {
        printf("Synchronization successful!\nExpected => %d\nReceived => %d\n", (threads_amount * section_amount), number);
    }

    return 0;
}
