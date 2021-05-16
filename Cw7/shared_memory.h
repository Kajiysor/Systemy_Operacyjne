#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

int create_shared_memory(const char *name);
void delete_shared_memory(const char *name);
int open_shared_memory(const char *name);
void close_shared_memory(int fd);
void set_shared_memory_size(int fd, off_t length);
void *map_shared_memory(int fd, size_t length);
void delete_shared_memory_mapping(void *addr, size_t length);

#endif