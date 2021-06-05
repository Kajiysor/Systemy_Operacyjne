#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "queue.h"

mqd_t queue_create(const char *name, int oflag)
{
    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MESSAGE_SIZE;
    mqd_t desc = mq_open(name, O_CREAT | O_EXCL | oflag, 0644, &attr);
    if (desc == -1)
    {
        perror("Error creating queue!\n");
        queue_delete(name);
        exit(EXIT_FAILURE);
    }
    return desc;
}

void queue_delete(const char *name)
{
    if (mq_unlink(name) == -1)
    {
        perror("Error deleting queue!\n");
        exit(EXIT_FAILURE);
    }
}

mqd_t queue_open(const char *name, int oflag)
{
    mqd_t desc = mq_open(name, oflag);
    if (desc == -1)
    {
        perror("Error opening queue!\n");
        exit(EXIT_FAILURE);
    }
    return desc;
}

void queue_close(mqd_t mq_des)
{
    if (mq_close(mq_des) == -1)
    {
        perror("Error closing queue!\n");
        exit(EXIT_FAILURE);
    }
}

void queue_send(mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio)
{
    if (mq_send(mq_des, msg_ptr, MESSAGE_SIZE, msg_prio) == -1)
    {
        perror("Error sending message!\n");
        exit(EXIT_FAILURE);
    }
}

void queue_receive(mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio)
{
    if (mq_receive(mq_des, msg_ptr, MESSAGE_SIZE, msg_prio) == -1)
    {
        perror("Error receiving message!\n");
        exit(EXIT_FAILURE);
    }
}

void queue_get_attributes(mqd_t mq_des, struct mq_attr *attr)
{
    if (mq_getattr(mq_des, attr) == -1)
    {
        perror("Error getting queue attributes!\n");
        exit(EXIT_FAILURE);
    }
}