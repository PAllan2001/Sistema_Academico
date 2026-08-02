#ifndef HISTORICO_H
#define HISTORICO_H

#include "conexao.h"

typedef struct
{
    int idHistorico;
    int idAluno;
    int idMateria;
    int nota;
    
} Historico;

void cadastrarHistorico(SQLHDBC conexao, Historico historico);
void listarHistorico(SQLHDBC conexao);
void buscarHistoricoRA(SQLHDBC conexao, int ra);

#endif