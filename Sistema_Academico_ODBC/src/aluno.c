#include "aluno.h"
#include <stdio.h>
#include "conexao.h"
 


int id_Aluno;
int ra;
char nome_Completo[100];


void cadastrarAluno(SQLHDBC conexao, Aluno aluno)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    retorno = SQLAllocHandle(SQL_HANDLE_STMT, conexao, &stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        printf("Erro ao criar o Statement.\n");
        return;
    }

    retorno = SQLPrepare(
        stmt,
        (SQLCHAR *)"INSERT INTO aluno (ra, nome_completo) VALUES (?, ?)",
        SQL_NTS);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLBindParameter(
        stmt,
        1,
        SQL_PARAM_INPUT,
        SQL_C_LONG,
        SQL_INTEGER,
        0,
        0,
        &aluno.ra,
        0,
        NULL);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLBindParameter(
        stmt,
        2,
        SQL_PARAM_INPUT,
        SQL_C_CHAR,
        SQL_VARCHAR,
        100,
        0,
        aluno.nome,
        0,
        NULL);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLExecute(stmt);

    if (SQL_SUCCEEDED(retorno))
    {
        printf("Aluno cadastrado com sucesso!\n");
    }
    else
    {
        exibirErroODBC(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}
void listarAlunos(SQLHDBC conexao)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    int idAluno;
    int ra;
    char nome[100];

    const char sql[] =
        "SELECT id_aluno, ra, nome_completo FROM aluno";

    retorno = SQLAllocHandle(SQL_HANDLE_STMT, conexao, &stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        printf("Erro ao criar o Statement.\n");
        return;
    }

    retorno = SQLPrepare(stmt, (SQLCHAR *)sql, SQL_NTS);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    printf("\n===== LISTA DE ALUNOS =====\n\n");

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt, 1, SQL_C_LONG, &idAluno, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &ra, 0, NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR, nome, sizeof(nome), NULL);

        printf("ID: %d\n", idAluno);
        printf("RA: %d\n", ra);
        printf("Nome: %s\n", nome);
        printf("-------------------------\n");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void buscarAlunoPorRA(SQLHDBC conexao, int ra)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    int idAluno;
    char nome[100];

    const char sql[] =
        "SELECT id_aluno, ra, nome_completo FROM aluno WHERE ra = ?";

    retorno = SQLAllocHandle(SQL_HANDLE_STMT, conexao, &stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        printf("Erro ao criar o Statement.\n");
        return;
    }

    retorno = SQLPrepare(stmt, (SQLCHAR *)sql, SQL_NTS);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLBindParameter(
        stmt,
        1,
        SQL_PARAM_INPUT,
        SQL_C_LONG,
        SQL_INTEGER,
        0,
        0,
        &ra,
        0,
        NULL);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLFetch(stmt);

    if (SQL_SUCCEEDED(retorno))
    {
        SQLGetData(stmt, 1, SQL_C_LONG, &idAluno, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &ra, 0, NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR, nome, sizeof(nome), NULL);

        printf("\nAluno encontrado:\n");
        printf("ID: %d\n", idAluno);
        printf("RA: %d\n", ra);
        printf("Nome: %s\n", nome);
    }
    else
    {
        printf("Nenhum aluno encontrado com esse RA.\n");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void atualizarAluno(SQLHDBC conexao, Aluno aluno)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;
    SQLLEN linhasAfetadas;

    const char sql[] =
        "UPDATE aluno SET nome_completo = ? WHERE ra = ?";

    retorno = SQLAllocHandle(SQL_HANDLE_STMT, conexao, &stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        printf("Erro ao criar o Statement.\n");
        return;
    }

    retorno = SQLPrepare(stmt, (SQLCHAR *)sql, SQL_NTS);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLBindParameter(
        stmt,
        1,
        SQL_PARAM_INPUT,
        SQL_C_CHAR,
        SQL_VARCHAR,
        100,
        0,
        aluno.nome,
        0,
        NULL);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLBindParameter(
        stmt,
        2,
        SQL_PARAM_INPUT,
        SQL_C_LONG,
        SQL_INTEGER,
        0,
        0,
        &aluno.ra,
        0,
        NULL);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLExecute(stmt);

    if (SQL_SUCCEEDED(retorno))
    {
        SQLRowCount(stmt, &linhasAfetadas);

        if (linhasAfetadas > 0)
        {
            printf("Aluno atualizado com sucesso!\n");
        }
        else
        {
            printf("Aluno nao encontrado.\n");
        }
    }
    else
    {
        exibirErroODBC(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}
void excluirAluno(SQLHDBC conexao, int ra)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;
    SQLLEN linhasAfetadas;

    const char sql[] =
        "DELETE FROM aluno WHERE ra = ?";

    retorno = SQLAllocHandle(SQL_HANDLE_STMT, conexao, &stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        printf("Erro ao criar o Statement.\n");
        return;
    }

    retorno = SQLPrepare(stmt, (SQLCHAR *)sql, SQL_NTS);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLBindParameter(
        stmt,
        1,
        SQL_PARAM_INPUT,
        SQL_C_LONG,
        SQL_INTEGER,
        0,
        0,
        &ra,
        0,
        NULL);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    retorno = SQLExecute(stmt);

    if (SQL_SUCCEEDED(retorno))
    {
        SQLRowCount(stmt, &linhasAfetadas);

        if (linhasAfetadas > 0)
        {
            printf("Aluno excluido com sucesso!\n");
        }
        else
        {
            printf("Aluno nao encontrado.\n");
        }
    }
    else
    {
        exibirErroODBC(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}