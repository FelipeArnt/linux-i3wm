/*Arnt Shell */
#include <stdio.h>
#include <stdlib.h>
#define ASH_RL_BUFFSIZE 1024
/*---ash---*/
int main(int argc, char **argv)
{
  ash_loop();

  return EXIT_SUCCESS;
}

// Loop da shell 
void ash_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");

    line = ash_read_line();
    args = ash_split_line();
    status = ash_execute();

    free(line);
    free(args);
    while(status);
  }
}

// Executor da shell 
void ash_execute()
{

}

char ash_read_line(void)
{
  int bufsize = ASH_RL_BUFFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer){
    fprint(stderr, "ash: erro ao alocar\n");
    exit(EXIT_FAILURE);
  }

  while (1) {

    c = get.char();

    if (c == EOF || c == "\n"){
      buffer[position] = "\0";
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize){
      bufsize = ASH_RL_BUFFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer)
      {
        fprintf(stderr, "ash: erro ao alocar\n");
        exit(EXIT_FAILURE);
      }
    }


  }

}
