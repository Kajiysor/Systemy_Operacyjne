#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include "queue.h"

mqd_t server;

void closing(void)
{
    queue_close(server);
}

void my_sig_handler(int signal)
{
    printf("Interruption signal, deleting queue!\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    char answer_queue_name[10];
    mqd_t answer_queue;
    char reading[MESSAGE_SIZE];
    char message[MESSAGE_SIZE + 10];
    struct mq_attr answer_attr, server_attr;

    sprintf(answer_queue_name, "/%d", getpid());

    sleep(1);

    server = queue_open(QUEUE_NAME, O_WRONLY);
    queue_get_attributes(server, &server_attr);
    printf("Opened queue named \"%s\" with descriptor %d and attributes: \nFLAGS = %ld \nMAXMSG = %ld \nMSGSIZE = %ld \nCURMSGS = %ld  \n",
           QUEUE_NAME, server, server_attr.mq_flags, server_attr.mq_maxmsg, server_attr.mq_msgsize, server_attr.mq_curmsgs);

    if (atexit(closing) != 0)
    {
        perror("Atexit function error!\n");
        _exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, my_sig_handler) == SIG_ERR)
    {
        perror("Signal error!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    sleep(rand() % 3 + 1);

    while (1)
    {
        printf("Enter the operation:\n");
        if (scanf("%s", reading) == EOF)
        {
            printf("\n============================================\n");
            printf("Reading has ended, you may now close the terminal window!\n");
            exit(EXIT_SUCCESS);
        }

        sprintf(message, "[%d] %s", getpid(), reading);

        queue_send(server, message, 1);
        printf("\nSent request to server: %s\n", message);

        answer_queue = queue_create(answer_queue_name, O_RDONLY);
        queue_get_attributes(answer_queue, &answer_attr);
        printf("Created queue named \"%s\" with descriptor %d and attributes: \nFLAGS = %ld \nMAXMSG = %ld \nMSGSIZE = %ld \nCURMSGS = %ld  \n",
               answer_queue_name, answer_queue, answer_attr.mq_flags, answer_attr.mq_maxmsg, answer_attr.mq_msgsize, answer_attr.mq_curmsgs);

        printf("Waiting for the server to respond!\n");
        queue_receive(answer_queue, message, NULL);
        printf("Received from server: %s\n\n", message);

        queue_close(answer_queue);
        queue_delete(answer_queue_name);

        sleep(2);
    }

    queue_close(server);

    printf("\n\nCLIENT: END OF PROCESS\n");

    return 0;
}