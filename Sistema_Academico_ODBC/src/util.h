#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>


int lerInteiro(const char *mensagem);
int lerRA(const char *mensagem);
int LerNota (const char *mensagem);

void lerTexto(const char *mensagem, char texto[], int tamanho);

void limparBuffer();


#endif