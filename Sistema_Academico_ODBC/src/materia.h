#ifndef MATERIA_H
#define MATERIA_H

#include "conexao.h"

typedef struct
{
    int id;
    char nome[100];
    int cargaHr;
} Materia;

void cadastrarMateria(SQLHDBC conexao,Materia materia);
void listarMaterias(SQLHDBC conexao);
void buscarMateriaNome(SQLHDBC conexao, char nomeBusca[]);
void atualizarMateria(SQLHDBC conexao, Materia materia);
void excluirMateria(SQLHDBC conexao, int id);

#endif