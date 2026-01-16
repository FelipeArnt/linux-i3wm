# include <stdio.h>          /* Requisito para o printf()*/
# include <stdlib.h>         /* Requisito para free() malloc(), realloc() e exit();*/
# include <string.h>         /* Requisito para strcmp()*/

#define p(...) printf(__VA_ARGS__);

#define DEL " "

void gash_split_line(char *line)
{
  char *tokens[6] = {0};
  int posicao;

  posicao = 0;
  for (char *token = strtok(line, DEL); token; token = strtok(NULL, DEL)){
    tokens[posicao++] = token;
  }

  posicao = 0;
  while (tokens[posicao]){
    p("%s\n", tokens[posicao++]);
  }
}

int int main(void)
{
  char s[] = "ls -la README.md | bat";
    gash_split_line(s);

  return EXIT_SUCCESS;
}

