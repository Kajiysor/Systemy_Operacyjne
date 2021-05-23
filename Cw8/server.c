#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include "queue.h"

void deleting(void)
{
    queue_delete(QUEUE_NAME);
}

void my_sig_handler(int signal)
{
    printf("\nInterruption signal, deleting queue!\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    int client_PID;
    float number1, number2, result;
    char operator;
    char message[MESSAGE_SIZE];
    char result_s[MESSAGE_SIZE];
    mqd_t queue_desc, answer;
    struct mq_attr attr;

    queue_desc = queue_create(QUEUE_NAME, O_RDONLY);
    queue_get_attributes(queue_desc, &attr);
    printf("Created queue named \"%s\" with descriptor %d and attributes: \nFLAGS = %ld \nMAXMSG = %ld \nMSGSIZE = %ld \nCURMSGS = %ld  \n",
           QUEUE_NAME, queue_desc, attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    if (atexit(deleting) != 0)
    {
        perror("Atexit function erorr!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, my_sig_handler) == SIG_ERR)
    {
        perror("Signal error!\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    while (1)
    {
        queue_receive(queue_desc, message, NULL);

        sscanf(message, "[%d] %f%c%f", &client_PID, &number1, &operator, & number2);

        printf("Received request from [%d] ==> %f %c %f\n", client_PID, number1, operator, number2);

        if (operator== '+')
        {
            result = number1 + number2;
            sprintf(result_s, "%f", result);
        }
        else if (operator== '-')
        {
            result = number1 - number2;
            sprintf(result_s, "%f", result);
        }
        else if (operator== '*')
        {
            result = number1 * number2;
            sprintf(result_s, "%f", result);
        }
        else if (operator== '/' || operator== ':')
        {
            result = number1 / number2;
            sprintf(result_s, "%f", result);
        }
        else
        {
            sprintf(result_s, "Erorr: Unknown operator!\n");
        }

        sleep(rand() % 3 + 1);

        sprintf(message, "/%d", client_PID);
        answer = queue_open(message, O_WRONLY);

        printf("Sending answer \"%s\" to process [%d]\n", result_s, client_PID);
        queue_send(answer, result_s, 1);
        queue_close(answer);
    }

    queue_delete(QUEUE_NAME);

    printf("\n\n SERVER: END OF PROCESS!\n");

    return 0;
}