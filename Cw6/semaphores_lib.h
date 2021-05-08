#ifndef SEMAPHORES_LIB_H
#define SEMAPHORES_LIB_H

sem_t *create_semaphore(const char *name);
sem_t *open_semaphore(const char *name);
void close_semaphore(sem_t *sem_t);
void delete_semaphore(const char *name);
void semaphore_V(sem_t *sem);
void semaphore_P(sem_t *sem);
void semaphore_value(sem_t *sem, int *sval);

#endif