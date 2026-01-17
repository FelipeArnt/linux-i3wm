#include "vsw.h"

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
    p(G "\n["RST"vsw-shell"G"]-"RST"By"G"-["RST"FelipeArnt"G"]\n\n");
    p(G "  _    ________      __            _____ __  __________    __ \n"
        "| |  / / ___/ |     / /           / ___// / / / ____/ /   / / \n"
        "| | / /\\__ \\| | /| / /  ______    \\__ \\/ /_/ / __/ / /   / /  \n"
        "| |/ /___/ /| |/ |/ /  /_____/   ___/ / __  / /___/ /___/ /___\n"
        "|___//____/ |__/|__/            /____/_/ /_/_____/_____/_____/\n\n" RST
  );
}
