#ifndef HTML_H
#define HTML_H

#include "serie.h"
#include "historico.h"

typedef struct {
    char *data;
    size_t size;
}Buffer;

char** buscaatores(const char *str, int *quantAtores);
float buscarating(const char *str);
int buscaranking(const char *str);
char* buscaenredo(const char *str);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
void extraiHTML(Serie serie[], int i);


#endif
