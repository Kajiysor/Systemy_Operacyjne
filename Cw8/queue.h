#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_NAME "/message_queue"
#define MAX_MESSAGES 10
#define MESSAGE_SIZE 30

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "queue.h"

mqd_t queue_create(const char *name, int oflag);
void queue_delete(const char *name);
mqd_t queue_open(const char *name, int oflag);
void queue_close(mqd_t mq_des);
void queue_send(mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio);
void queue_receive(mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio);
void queue_get_attributes(mqd_t mq_des, struct mq_attr *attr);

#endif