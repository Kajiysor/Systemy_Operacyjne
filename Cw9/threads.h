#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

pthread_t thread_create(void* function(void *), void *argument);
void thread_join(pthread_t thread);
void mutex_init(pthread_mutex_t *mutex);
void mutex_delete(pthread_mutex_t *mutex);
void mutex_open(pthread_mutex_t *mutex);
void mutex_close(pthread_mutex_t *mutex);

#endif