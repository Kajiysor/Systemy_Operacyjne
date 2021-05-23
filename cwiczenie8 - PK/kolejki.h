#ifndef DZIELONA_H
#define DZIELONA_H

#define KOLEJKA_NAZWA "/kolejka_komunikatow"
#define MAX_WIADOMOSCI 10
#define DLUGOSC_KOMUNIKATU 30

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "kolejki.h"

mqd_t kolejka_utworz (const char *name, int oflag);
mqd_t kolejka_otworz (const char *name, int oflag);
void kolejka_wyslij (mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio);
void kolejka_odbierz (mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio);
void kolejka_zamknij (mqd_t mq_des);
void kolejka_usun (const char *name);

#endif