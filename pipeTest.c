
// C program to implement pipe in Linux
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 80
#define MAX_ARGS 40
#define HISTORY_PATH ".history"

int p_wait;
int in_file, out_file;
int saved_in, saved_out;
int in, out;
int pipe_ind;
int save_c;

int main()
{
    char command[MAX_LINE];
    char last_command[MAX_LINE];
    char parse_command[MAX_LINE];
    char *args[MAX_ARGS];
    char *argsp1[MAX_ARGS], *argsp2[MAX_ARGS];
    int should_run = 1, history = 0;
    int alert;
    int pipech[2];


    while(should_run){
        printf("osh> ");

        fflush(stdout);

        fgets(command, 80, stdin);

        strcpy(parse_command, command);

        //parse Input
        int args_count = 0;
        int command_len = strlen(command);
        int arg_start = -1;
        for(int i = 0; i < command_len; i++)
        {
            if(command[i] == ' ' || command[i] == '\t' || command[i] == '\n')
            {
            if(arg_start != -1)
            {
                args[args_count++] = &command[arg_start];
                arg_start = -1;
            }
            command[i] = '\0';
            }
            else
            {
            if(command[i] == '&')
            {
                p_wait = 0;
                i = command_len;
            }
            if(arg_start == -1) arg_start = i;
            }
        }
        args[args_count] = NULL;
        // end of parse input


        //if the command is "exit"
        if(!strcmp(args[0], "exit")) //if both strings are equal, 0 is returned, so we have to use ! to turn 0 into a truthy value
        {
        should_run = 0;
        continue;
        }
        //end of exit

        int pipe[2];
        char string[100];
        if(pipe(pipe) == - 1){
            printf("Failed to create pipe\n");
            exit(1);
        }
    }

    // array of 2 size a[0] is for reading 
    // and a[1] is for writing over a pipe 
    int a[2]; 
  
    // opening of pipe using pipe(a)   
    char buff[10];
    if (pipe(a) == -1) 
    {
        perror("pipe"); // error in pipe
        exit(1); // exit from the program
    }
  
    // writing a string "code" in pipe
    write(a[1], "code", 5); 
    printf("\n");
  
    // reading pipe now buff is equal to "code"
    read(a[0], buff, 5);
  
    // it will print "code"
    printf("%s", buff); 
}