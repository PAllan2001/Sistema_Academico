#ifndef ALUNO_H
#define ALUNO_H

#include "conexao.h"

typedef struct
{
    int id;
    int ra;
    char nome[100];
} Aluno;

void cadastrarAluno(SQLHDBC conexao, Aluno aluno);
void listarAlunos(SQLHDBC conexao);
void buscarAlunoPorRA(SQLHDBC conexao, int ra);
void atualizarAluno(SQLHDBC conexao, Aluno aluno);
void excluirAluno(SQLHDBC conexao, int ra);

#endif