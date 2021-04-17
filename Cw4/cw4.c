#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>
 
int main( int argc, char* argv[] ) {

    int text_file_descriptor, id;
    int pipe_file_descriptor[2];
    char buffer[10];
    ssize_t num_bytes;

    if (argv < 3){
        printf("Please provide the source file as the first argument and the output file as a second argument!\n");
        exit(10);
    }

    pipe(pipe_file_descriptor);

    id = fork();

    switch(id)
    {
        case -1:
            printf("fork error");
            exit(1);

        case 0:
            close(pipe_file_descriptor[1]);
            text_file_descriptor = open(argv[2], O_WRONLY | O_CREAT, 0644);
            if (text_file_descriptor == -1){
                printf("Error opening output file");
                exit(2);
            }
            while(1){
                sleep(rand()%3);

                num_bytes = read(pipe_file_descriptor[0], buffer, sizeof(buffer));
                if (num_bytes == -1) {
                    printf("Pipe reading error");
                    exit(3);
                }
                else if (num_bytes == 0){
                    break;
                }
                else {
                    buffer[num_bytes] = 0;
                    write(text_file_descriptor, buffer, strlen(buffer));
                    printf("====================\nConsumer Received:\n");
                    write(1, buffer, strlen(buffer));
                    printf("\n====================\n\n");
                }
            }
            close(text_file_descriptor);
            close(pipe_file_descriptor[0]);
            exit(0);

        default:
            close(pipe_file_descriptor[0]);
            text_file_descriptor = open(argv[1], O_RDONLY, 0644);
            if (text_file_descriptor == -1){
                printf("Error opening source file");
                exit(4);
            }
            while(1){
                sleep(rand()%3);

                num_bytes = read(text_file_descriptor, buffer, sizeof(buffer));
                if (num_bytes == -1) {
                    printf("Pipe reading error");
                    exit(5);
                }
                else if (num_bytes == 0){
                    break;
                }
                else {
                    buffer[num_bytes] = 0;
                    write(pipe_file_descriptor[1], buffer, sizeof(buffer));
                    printf("====================\nManufacturer Sent:\n");
                    write(1, buffer, strlen(buffer));
                    printf("\n====================\n\n");
                }
            }
            close(text_file_descriptor);
            close(pipe_file_descriptor[1]);
            wait(NULL);


    }

    return 0;
}