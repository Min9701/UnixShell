#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  //STDIN_FILENO, STDOUT_FILENO
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 25
#define MAX_LINE 80
#define MAX_ARGS 40

int p_wait;
int in_file, out_file;
int saved_in, saved_out;
int in, out;
int pipe_ind;
int save_c;

void parseInput(char *command, char **args)
{
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
  //ei: osh> mkdir ddd
  // the result:
  // args[0] == mkdir
  // args[1] == ddd
  // args[2] == NULL
}

int main(){
    char last_command[MAX_LINE];
    char parse_command[MAX_LINE];
    char *args[MAX_ARGS];
    char *argsp1[MAX_ARGS], *argsp2[MAX_ARGS];
    int should_run = 1, history = 0;
    int alert;
    

    p_wait = 1;
    alert = 0;
    out_file = in_file = -1;
    pipe_ind = -1;
    save_c = 1;

    /////////////////////////////////////////////////////

    char command[BUFFER_SIZE];

    printf("osh> ");
    fgets(command,BUFFER_SIZE,stdin); 

    parseInput(command, args);

    for(int i = 0; i< strlen(args); i++){
        printf(args[i]);
    }

}