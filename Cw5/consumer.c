#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
 
int main( int argc, char* argv[] ) {

    int text_file_descriptor, fifo_file_descriptor;
    //int pipe_file_descriptor[2];
    char buffer[10];
    ssize_t num_bytes;

    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL){
        printf("Please provide the source file as the first argument, output file as a second argument and FIFO name as the third argument!\n");
        exit(10);
    }

    printf("OPENING FIFO FILE DESCRIPTOR IN CONSUMER FOR READING");
    //pipe(pipe_file_descriptor);
    fifo_file_descriptor = open(argv[3], O_RDONLY);
    if (fifo_file_descriptor == -1){
        return 8;
    }

    //close(pipe_file_descriptor[1]);
    text_file_descriptor = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (text_file_descriptor == -1){
        printf("Error opening output file");
        exit(2);
    }
    while(1){
        sleep(rand()%3);

        num_bytes = read(fifo_file_descriptor, buffer, sizeof(buffer));
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
    close(fifo_file_descriptor);
    exit(0);




    return 0;
}