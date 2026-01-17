#define _GNU_SOURCE          // Requisito para o getline()
#include <stdio.h>           // Requisito para o printf()
#include <unistd.h>          // Requisito para fork()
#include <sys/wait.h>        // Requisito para waitpid()
#include <stdlib.h>          // Requisito para free(), malloc(), realloc() e exit()
#include <string.h>          // Requisito para strcmp()
#include "vsw.h"

/*
 * Shell builtins
 */
int vsw_cd(char **args);
int vsw_help(char **args);
//int vsw_roteador(char **args);
int vsw_checksum(char **args);
int vsw_hexsend(char **args);
int vsw_exit(char **args);
//int vsw_tvbox(char **args);
//int vsw_alias(char **args);


char *builtin_str[] = {
    "cd",
    "help",
    "ajuda",
//    "roteador",
    "checksum",
    "hexsend",
//    "tvbox",
//    "alias",
    "exit",
};

int (*builtin_func[]) (char **) = {
    &vsw_cd,
    &vsw_help,
    &vsw_help,
//    &vsw_roteador,
    &vsw_checksum,
    &vsw_hexsend,
//  &vsw_tvbox,
//  &vsw_alias,
    &vsw_exit,
};

int vsw_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/* [Implementando Funções Builtins] */

int vsw_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, G"["Y"vsw"G"]:"RST"Era esperado um argumento para \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror(Y"[vsw]");
        }
    }
    return 1;
}

int vsw_help(char **args)
{
    (void)args;  // Evita warning de unused paramete 

    printf(G"["RST"vsw-shell" G"]: "RST"Digite nome de programas, argumentos e pressione enter!!\n");
    printf(G"["RST"vsw-shell" G"] - [" RST"Ensaios Funcionais" G"] \n");

    for (int i = 0; i < vsw_num_builtins(); i++) {
        printf(" %s\n", builtin_str[i]);
    }
    printf(G"["RST"vsw-shell" G"]: "RST"Use o comando man para exibir informações de outros programas!!\n");

    return 1;
}
/*      <--TODO-->
int vsw_roteador(char **args) --> usar o script router.sh do roadmap-LM
{
        if (args[1] == NULL) {
        printf(G"[roteador]:" RST"Uso: roteador <alvo> [tipo]\n");
        printf(" Tipos: vuln, normal\n");
        return 1;
    }

    char cmd[4096] = {0};
    const char *target = args[1];
    const char *type = args[2] ? args[2] : "/usr/local/bin/roteador";

    printf("[ensaio roteador] Executando: %s\n", cmd);
    return system(cmd); // Simplifica execução complexa
}


int vsw_tvbox(char **args) ---> usar o script tvbox.sh do roadmap-LM
{
  int return_status = system("/usr/local/bin/tvbox") 
}
*/

int vsw_checksum(char **args)
{
    if (args[1] == NULL || args[2] == NULL) {
        printf("[checksum] Uso: checksum <file> <sha256|crc32|md5>\n");
        return 1;
    }

    char cmd[512];
    const char *file = args[1];
    const char *type = args[2];

    if (strcmp(type, "sha256") == 0)
        snprintf(cmd, sizeof(cmd), "sha256sum %s", file);
    else if (strcmp(type, "crc32") == 0)
        snprintf(cmd, sizeof(cmd), "crc32 %s", file);
    else if (strcmp(type, "md5") == 0)
        snprintf(cmd, sizeof(cmd), "md5sum %s", file);
    else {
        printf("[checksum] Tipo inválido\n");
        return 1;
    }

    return system(cmd);
}

int vsw_hexsend(char **args)
{
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        printf("[hexsend] Uso: hexsend <host> <port> <hex_string>\n");
        printf("  Ex: hexsend 192.168.1.10 8080 '48656c6c6f'\n");
        return 1;
    }

    char cmd[512];
    snprintf(cmd, sizeof(cmd), 
        "echo -n \"%s\" | xxd -r -p | nc -w 1 %s %s", 
        args[3], args[1], args[2]);

    printf("[hexsend] Enviando para %s:%s\n", args[1], args[2]);
    return system(cmd);
}



int vsw_exit(char **args)
{
    (void)args;  // Evita warning de unused parameter
    
    printf("[vsw]: Saindo...\n");
    return 0;
}

/* [Executor da shell] */

int vsw_launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* processo filho */
        if (execvp(args[0], args) == -1) {
            perror("[vsw]");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* erro no fork */
        perror("[vsw]");
    } else {
        /* processo pai */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int vsw_execute(char **args)
{
    if (args[0] == NULL) {
        return 1; /* Comando vazio foi digitado */
    }

    for (int i = 0; i < vsw_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return vsw_launch(args);
}

// Loop da shell 
void vsw_loop(void)
{
    char *line;
    char **args;
    int status;

    // Carregar histórico se existir
    system("test -f .vsw_history && history -r .vsw_history");

    do {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf(G "["RST"vsw" G"] %s " RST "> ", cwd);
        else
            printf(G "[vsw] ? " RST "> ");

        line = vsw_read_line();
        if (!line) break;

        // Salvar no histórico
        FILE *h = fopen(".vsw_history", "a");
        if (h) {
            fprintf(h, "%s\n", line);
            fclose(h);
        }

        args = vsw_split_line(line);
        status = vsw_execute(args);

        free(line);
        free(args);
    } while (status);}
    
#define vsw_TOK_BUFSIZE 64
#define vsw_TOK_DELIM " \t\r\n\a"

char **vsw_split_line(char *line)
{
    int bufsize = vsw_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));  /* CORRIGIDO: sizeof(char*) */
    char *token;

    if (!tokens) {
        fprintf(stderr, "[vsw:error]: Erro ao alocar\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, vsw_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += vsw_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));  /* CORRIGIDO: sizeof(char*) */
            if (!tokens) {
                fprintf(stderr, "[vsw:error]: Erro ao alocar\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, vsw_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char *vsw_read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            printf("\n");  // Nova linha limpa no EOF (Ctrl+D)
        } else {
            perror("[vsw:error]: getline falhou");
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
    vsw_loop();
    return EXIT_SUCCESS;
}
