/*[GabiShell]*/
#define _GNU_SOURCE          // Requisito para o getline()
#include <stdio.h>           // Requisito para o printf()
#include <unistd.h>          // Requisito para fork()
#include <sys/wait.h>        // Requisito para waitpid()
#include <stdlib.h>          // Requisito para free(), malloc(), realloc() e exit()
#include <string.h>          // Requisito para strcmp()
#include "gash.h"
/*---[Gash]---*/

/*
 * Shell builtins
 */
int gash_cd(char **args);
int gash_help(char **args);
int gash_fumei(char **args);
int gash_exit(char **args);
int gash_amor(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "fumei",
    "exit",
    "amor",
};

int (*builtin_func[]) (char **) = {
    &gash_cd,
    &gash_help,
    &gash_fumei,
    &gash_exit,
    &gash_amor,
};

int gash_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/* [Implementando Funções Builtins] */

int gash_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "[gash]: Era esperado um argumento para \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("[gash]");
        }
    }
    return 1;
}

int gash_help(char **args)
{
    (void)args;  // Evita warning de unused parameter
    
    printf("[gash] - [GabiShell] by FelipeArnt\n");
    printf("[gash]: Digite nome de programas, argumentos e pressione enter!!\n");
    printf("[gash:builtins]:  \n");

    for (int i = 0; i < gash_num_builtins(); i++) {
        printf(" %s\n", builtin_str[i]);
    }

    printf("[gash]: Use o comando man para exiber informações de outros programas...\n");
    return 1;
}

int gash_fumei(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "[gash]: Era esperado o número de cigarros fumados para o comando \"fumei\"\n");
        return 1;
    }
    
    // Implementação simples: apenas registra e exibe
    printf("[gash]: Registrado %s cigarros. Pare de fumar, desgraçado!\n", args[1]);
    return 1;
}

int gash_amor(char **args)
{
    (void)args;  // Evita warning de unused parameter
    
    printf("Eu te amo GabiDalla\n");
    return 1;
}

int gash_exit(char **args)
{
    (void)args;  // Evita warning de unused parameter
    
    printf("[gash]: Saindo...\n");
    return 0;
}

/* [Executor da shell] */

int gash_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* processo filho */
        if (execvp(args[0], args) == -1) {
            perror("[gash]");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* erro no fork */
        perror("[gash]");
    } else {
        /* processo pai */
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int gash_execute(char **args)
{
    if (args[0] == NULL) {
        return 1; /* Comando vazio foi digitado */
    }

    for (int i = 0; i < gash_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return gash_launch(args);
}

// Loop da shell 
void gash_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf(G "[ <3 ] %s " RST "> ", cwd);
        } else {
            printf(G "[ <3 ] ? " RST "> ");
        }

        line = gash_read_line();
        if (!line) {
            break;  // EOF ou erro
        }

        args = gash_split_line(line);
        status = gash_execute(args);

        free(line);
        free(args);
    } while (status);
}

#define GASH_TOK_BUFSIZE 64
#define GASH_TOK_DELIM " \t\r\n\a"

char **gash_split_line(char *line)
{
    int bufsize = GASH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));  /* CORRIGIDO: sizeof(char*) */
    char *token;

    if (!tokens) {
        fprintf(stderr, "[gash]: Erro ao alocar\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, GASH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += GASH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));  /* CORRIGIDO: sizeof(char*) */
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

char *gash_read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            printf("\n");  // Nova linha limpa no EOF (Ctrl+D)
        } else {
            perror("[gash]: getline falhou");
        }
        free(line);
        return NULL;
    }
    
    // Remove newline do final
    size_t len = strlen(line);
    if (len > 0 && line[len-1] == '\n') {
        line[len-1] = '\0';
    }
    
    return line;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    exibebanner();
    gash_loop();
    return EXIT_SUCCESS;
}
