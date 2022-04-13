#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

//execute ls -1 | wc

int main(void){
    char writeMessage[BUFFER_SIZE] = "ls";
    char readMessage[BUFFER_SIZE];
    int fd[2]; //construct an ordinary pipe
    pid_t pid1;

    //create the pipe and if sth bad happens
    if(pipe(fd) == -1){ //if the read_end is == -1
        printf("Failed to create a pipe");
        return 1;
    }

    //fork a child process
    pid1 = fork();

    if(pid1<0){
        fprintf(stderr, "Fork failed!");
        return 2;
    }

    if(pid1 >0){ //parent-process
        //close the unused end of the pipe
        close(fd[READ_END]);

        //write to the pipe
        write(fd[WRITE_END], writeMessage, strlen(writeMessage)+1);

        //close the write end of the pipe
        close(fd[WRITE_END]);        
    } 
    else { //child process - ls
        //close the unused end of the pipe
        close(fd[WRITE_END]);

        //read from the pipe
        read(fd[READ_END], readMessage, BUFFER_SIZE);
        // // printf("in the child process, and is reading the pipe: %s", readMessage);
        execlp(readMessage, readMessage, NULL);

        close(fd[READ_END]);
        //close the read end of the pipe

    }
    
    return 0;
}