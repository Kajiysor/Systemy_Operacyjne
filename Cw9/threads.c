#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

pthread_t thread_create(void *function(void *), void *argument)
{
    pthread_t thread_id;
    int status = pthread_create(&thread_id, NULL, function, argument);
    if (status == EAGAIN)
    {
        printf("Error creating thread!\n");
        printf ("System thread limit exceeded!\n");
        exit(EXIT_FAILURE);
    } 
    else if (status == ENOMEM)
    {
        printf("Error creating thread!\n");
        printf("Not enough memory to create new thread!\n");
        exit(EXIT_FAILURE);
    } 
    else if (status == EINVAL)
    {
        printf("Error creating thread!\n");
        printf("Nieprawidłowa wartość argumentu attr");
        exit(EXIT_FAILURE);
    } 
    else if (status != 0) {
        printf("Unknown error while creating thread!\n");
        exit(EXIT_FAILURE);
    }
    return thread_id;
}

void thread_join(pthread_t thread)
{
    if (pthread_join (thread, NULL) != 0)
    {
        printf("Error joining thread\n");
        exit(EXIT_FAILURE);	
    }
}

void mutex_init(pthread_mutex_t *mutex)
{
    if (pthread_mutex_init(mutex, NULL) != 0)
    {
		printf("Error while initializing mutex!\n");
		exit(EXIT_FAILURE);
	}
}

void mutex_delete(pthread_mutex_t *mutex)
{
    if (pthread_mutex_destroy (mutex) != 0)
    {
		printf ("Error while deleting mutex!\n");
		exit (EXIT_FAILURE);
	}
}

void mutex_open(pthread_mutex_t *mutex)
{
    if (pthread_mutex_unlock(mutex) != 0)
    {
		printf("Error while opening mutex!\n");
		exit(EXIT_FAILURE);
	}
}

void mutex_close(pthread_mutex_t *mutex)
{
    if (pthread_mutex_lock(mutex) != 0)
    {
        printf("Error while closing mutex!\n");
        exit(EXIT_FAILURE);	
    }
}
