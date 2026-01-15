/*Gabi Shell */
#include <stdio.h>
#include <stdlib.h>
#define gash_RL_BUFFSIZE 1024
/*---Gash---*/
int main(int argc, char **argv)
{
  gash_loop();

  return EXIT_SUCCESS;
}

// Loop da shell 
void gash_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");

    line = gash_read_line();
    args = gash_split_line();
    status = gash_execute();

    free(line);
    free(args);
    while(status);
  }
}

// Executor da shell 
void gash_execute()
{

}

char gash_read_line(void)
{
  int bufsize = gash_RL_BUFFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer){
    fprint(stderr, "[gash]: erro ao alocar\n");
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
      bufsize = gash_RL_BUFFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer)
      {
        fprintf(stderr, "[gash]: erro ao alocar\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}
