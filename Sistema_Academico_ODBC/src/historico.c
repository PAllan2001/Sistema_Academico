#include "historico.h"
#include <stdio.h>
#include "conexao.h"

int idHistorico;
int idAluno;
int idMateria;
int nota;


void cadastrarHistorico(SQLHDBC conexao, Historico historico)
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
        (SQLCHAR *)"INSERT INTO historico (id_aluno, id_materia, nota) VALUES (?, ?, ?)",
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
        &historico.idAluno,
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
        &historico.idMateria,
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
        3,
        SQL_PARAM_INPUT,
        SQL_C_LONG,
        SQL_INTEGER,
        0,
        0,
        &historico.nota,
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
        printf("Historico cadastrado com sucesso!\n");
    }
    else
    {
        exibirErroODBC(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void listarHistorico(SQLHDBC conexao)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    int nota;
    int ra;
    char nomeAluno[100];
    char nomeMateria[100];
    char situacao[15];

    const char sql[] =
        "SELECT a.ra, "
        "a.nome_completo, "
        "m.nome_materia, "
        "h.nota, "
        "CASE "
        "WHEN h.nota >= 7 THEN 'Aprovado' "
        "ELSE 'Reprovado' "
        "END AS situacao "
        "FROM historico h "
        "INNER JOIN aluno a ON h.id_aluno = a.id_aluno "
        "INNER JOIN materia m ON h.id_materia = m.id_materia "
        "ORDER BY a.nome_completo, m.nome_materia";

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
retorno = SQLFetch(stmt);

if (retorno == SQL_NO_DATA)
{
    printf("Nenhum historico cadastrado.\n");
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return;
}

    printf("\n===== HISTORICO =====\n\n");

    do
    {
        SQLGetData(stmt, 1, SQL_C_LONG, &ra, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, nomeAluno, sizeof(nomeAluno), NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR, nomeMateria, sizeof(nomeMateria), NULL);
        SQLGetData(stmt, 4, SQL_C_LONG, &nota, 0, NULL);
        SQLGetData(stmt, 5, SQL_C_CHAR, situacao, sizeof(situacao), NULL);

        printf("RA: %d\n", ra);
        printf("Aluno: %s\n", nomeAluno);
        printf("Materia: %s\n", nomeMateria);
        printf("Nota: %d\n", nota);
        printf("Situacao: %s\n", situacao);
        printf("------------------------------\n");

    } while (SQLFetch(stmt) == SQL_SUCCESS);

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    }

void buscarHistoricoRA(SQLHDBC conexao, int ra)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    char nomeAluno[100];
    char nomeMateria[100];
    int nota;
    char situacao[15];

    const char sql[] =
        "SELECT a.nome_completo, "
        "m.nome_materia, "
        "h.nota, "
        "CASE "
        "WHEN h.nota >= 7 THEN 'Aprovado' "
        "ELSE 'Reprovado' "
        "END AS situacao "
        "FROM historico h "
        "INNER JOIN aluno a ON h.id_aluno = a.id_aluno "
        "INNER JOIN materia m ON h.id_materia = m.id_materia "
        "WHERE a.ra = ? "
        "ORDER BY m.nome_materia";

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

    if (SQLFetch(stmt) == SQL_NO_DATA)
    {
        printf("Nenhum historico encontrado para esse aluno.\n");
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    printf("\n===== HISTORICO DO ALUNO =====\n\n");

    do
    {
        SQLGetData(stmt, 1, SQL_C_CHAR, nomeAluno, sizeof(nomeAluno), NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, nomeMateria, sizeof(nomeMateria), NULL);
        SQLGetData(stmt, 3, SQL_C_LONG, &nota, 0, NULL);
        SQLGetData(stmt, 4, SQL_C_CHAR, situacao, sizeof(situacao), NULL);

        printf("Aluno: %s\n", nomeAluno);
        printf("Materia: %s\n", nomeMateria);
        printf("Nota: %d\n", nota);
        printf("Situacao: %s\n", situacao);
        printf("------------------------------\n");

    } while (SQLFetch(stmt) == SQL_SUCCESS);

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}