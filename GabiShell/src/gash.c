#include "gash.h"
/* Corrigido: removido #include "utils.c" - nunca inclua arquivos .c */

/* split que aloca dinamicamente */
char **gash_split_line(char *line)
{
    char **tokens;
    size_t posicao = 0;  /* Corrigido: usar size_t para consistência */
    size_t bufsize = BUFSIZ;

    tokens = Malloc(bufsize * sizeof *tokens);

    for (char *token = strtok(line, DEL); token; token = strtok(NULL, DEL)) {
        tokens[posicao++] = token;

        if (posicao >= bufsize) {
            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(*tokens));
        }
    }

    tokens[posicao] = NULL;
    return tokens;
}

char *gash_read_line(void)
{
    char *buf = NULL;
    size_t bufsize = 0;
    char cwd[BUFSIZ];

    if (!Getcwd(cwd, sizeof(cwd))) {  /* Corrigido: verifica retorno */
        strcpy(cwd, "?");  /* Fallback se getcwd falhar */
    }

    p(G "[ <3 ] %s" RST " >. ", cwd);

    if (getline(&buf, &bufsize, stdin) == -1) {
        free(buf);
        buf = NULL;

        if (feof(stdin)) {
            p(RED "\n[gash]:[ EOF ]!!!" RST "\n");
        } else {
            p(RED "[gash]: Getline falhou!" RST "\n");
        }
    }

    return buf;
}

/* Entry point */
int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    char *line;
    char **args;

    exibebanner();

    while (line = gash_read_line()) {
        if (!line)
            break;
    //args = gash_split_line();
    pid_t pid = fork();
    if (pid == 0) {
      execvp(args[0], args);
      perror("execvp falhou!");
      exit(EXIT_FAILURE);
    } else {
      waitpid(pid, &status, 0);    
    }
    args = gash_split_line();
    free(line);
    return EXIT_SUCCESS;
}
