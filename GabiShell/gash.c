/*Gabi Shell*/
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
//<!--TOOD--!> 
}

#define GASH_TOK_BUFFSIZE 64
#define GASH_TOK_DELIM "\t\r\n\a"
char **gash_split_line(char *line)
{
  int bufzise = GASH_TOK_BUFFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char));
  char *token;


  if (!tokens)
  {
    fprintf(stderr, "[gash]: Erro ao alocar\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, GASH_TOK_DELIM);
  while (token != NULL){
    tokens[position] = token;
    position++;

    if (position >= bufsize){
      bufsize += GASH_TOK_BUFFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "[gash]: Erro ao alocar\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, GASH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
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

