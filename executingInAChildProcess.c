#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){
    int pid = fork();
    if (pid == -1) return 1;

    if (pid ==0){
        //child process
        execlp("ls", "ls",NULL);
        
    } else{
        printf("\n");
        wait(NULL);
        printf("post processing");
    }

    //printf("sucess!\n");
    return 0;
}
