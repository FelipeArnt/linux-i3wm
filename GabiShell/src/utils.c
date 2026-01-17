#include "gash.h"

/* Wrappers */

void *Getcwd(char *buf, size_t size) {
    if (getcwd(buf, size) == NULL) {
        perror(RED "getcwd Falhou!" RST);
        return NULL;  /* Corrigido: retorna NULL em caso de erro */
    }
    return buf;
}

void *Malloc(size_t size)
{
    void *ptr;

    if (size == 0) {
        return NULL;
    }

    ptr = malloc(size);  /* Corrigido: alocar memória */
    if (!ptr) {
        perror(RED "Malloc Falhou!" RST);
        exit(EXIT_FAILURE);
    }
    
    return ptr;
}

void *Realloc(void *ptr, size_t size)
{
    void *novo_ptr;

    novo_ptr = realloc(ptr, size);
    if (!novo_ptr && size != 0) {
        perror(RED "Realloc Falhou!" RST);
        exit(EXIT_FAILURE);
    }

    return novo_ptr;
}

void exibebanner(void)
{
//    p(G "\n<-[gash]->[GABI-SHELL]-[INICIADA]<-[gash]->\n\n");
    p(G "\n<-[gash]-> [By][FelipeArnt] <-[gash]->\n\n");
//    p(G "\n<-[gash]-> [ READ-EVALUATE ] <-[gash]->\n\n");
//   p(G "\n<-[gash]-> [ PARSE-PRINT ] <-[gash]->\n\n");
//    p(G "\n<-[gash]-> [ EXECUTE-LOOP ] <-[gash]->\n\n");

    p(
        " /$$$$$$            /$$       /$$                       /$$                 /$$ /$$      \n"
        " /$$__  $$          | $$      |__/                      | $$                | $$| $$      \n"
        "| $$  \\__/  /$$$$$$ | $$$$$$$  /$$              /$$$$$$$| $$$$$$$   /$$$$$$ | $$| $$      \n"
        "| $$ /$$$$ |____  $$| $$__  $$| $$             /$$_____/| $$__  $$ /$$__  $$| $$| $$      \n"
        "| $$|_  $$  /$$$$$$$| $$  \\ $$| $$            |  $$$$$$ | $$  \\ $$| $$$$$$$$| $$| $$      \n"
        "| $$  \\ $$ /$$__  $$| $$  | $$| $$             \\____  $$| $$  | $$| $$_____/| $$| $$      \n"
        "|  $$$$$$/|  $$$$$$$| $$$$$$$/| $$             /$$$$$$$/| $$  | $$|  $$$$$$$| $$| $$      \n"
        " \\______/  \\_______/|_______/ |__/            |_______/ |__/  |__/ \\_______/|__/|__/      " RST "\n"
    );
}
