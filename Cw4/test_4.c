#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
 
int main( int argc, char* argv[] ) {
    int fdone[2];
    pid_t childid;
    ssize_t byte_num;
    char readBuff[16];
    char writeBuff[50];
    int readCounter;
 
    pipe( fdone );
 
    if( argc < 3 ) {
        printf( "Atleast need 2 params " );
        exit(1);
    }
 
    int fileOpen = open( argv[1], 0 );
    int targetFile = open(argv[2], O_WRONLY | O_CREAT, 0644);
     
    if ( fileOpen == -1 || targetFile == -1 ) {
        printf( "Opening file failed " );
        exit(1);
    }
    childid = fork();
 
    if( childid == 0 ) {
        // inside the child prcocess
        close( fdone[1] );
        memset(readBuff, 0, sizeof(readBuff));
 
        byte_num = read( fdone[0], readBuff, sizeof( readBuff ) );
        printf( "The recived string is : %s", readBuff );
 
        //Writing to the target fileOpen
        write( targetFile, readBuff, strlen( readBuff ) );
        close(targetFile);
        close(fdone[0]);
    } else {
        // inside the parent process
        close( fdone[0] );
        // code to read from a text file
        memset(readBuff, 0, sizeof(readBuff));
 
        while( (readCounter = read( fileOpen, readBuff, sizeof( readBuff ) ) > 0 ) )  {
        // if (byte_num == 0){
        //     break;
        // }
        write( fdone[1], readBuff, sizeof( readBuff ) );
        }
        close(fileOpen);
        close( fdone[1] );
    }
}