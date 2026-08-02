#include "materia.h"
#include <stdio.h>
#include "conexao.h"


int id;
char nome[100];
int cargaHr;


void cadastrarMateria(SQLHDBC conexao, Materia materia)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    // Cria o Statement
    retorno = SQLAllocHandle(SQL_HANDLE_STMT, conexao, &stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        printf("Erro ao criar o Statement.\n");
        return;
    }

    retorno = SQLPrepare(
        stmt,
        (SQLCHAR *)"INSERT INTO materia (nome_materia, carga_horaria) VALUES (?, ?)",
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
        SQL_C_CHAR,
        SQL_VARCHAR,
        100,
        0,
        materia.nome,
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
        &materia.cargaHr,
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
        printf("Materia cadastrada com sucesso!\n");
    }
    else
    {
        exibirErroODBC(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}
void listarMaterias(SQLHDBC conexao)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    int idMateria;
    char nomeMateria[100];
    int cargaHr;

    const char sql[] =
        "SELECT id_materia, nome_materia, carga_horaria FROM materia";

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

    printf("\n===== LISTA DE MATERIAS =====\n\n");

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        SQLGetData(stmt, 1, SQL_C_LONG, &idMateria, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, nomeMateria, sizeof(nomeMateria),NULL);
        SQLGetData(stmt, 3, SQL_C_LONG, &cargaHr, 0, NULL);

        printf("ID : %d\n", idMateria);
        printf("Nome : %s\n", nomeMateria);
        printf("Carga Horaria : %d\n", cargaHr);
        printf("-------------------------\n");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void buscarMateriaNome(SQLHDBC conexao, char nomeBusca[])
{
    SQLHSTMT stmt;
    SQLRETURN retorno;

    int idMateria;
    char nomeMateria[100];
    int cargaHr;

    char pesquisa[110];

    const char sql[] =
    "SELECT id_materia, nome_materia, carga_horaria "
    "FROM materia "
    "WHERE UPPER(nome_materia) LIKE UPPER(?)";

    retorno = SQLAllocHandle(SQL_HANDLE_STMT, conexao, &stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        printf("Erro ao criar o Statement.\n");
        return;
    }

    // Monta o padrão: %texto%
    snprintf(pesquisa, sizeof(pesquisa), "%%%s%%", nomeBusca);

    retorno = SQLPrepare(stmt, (SQLCHAR *)sql, SQL_NTS);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }
    SQLLEN tamanhoPesquisa = SQL_NTS;

    retorno = SQLBindParameter(
        stmt,
        1,
        SQL_PARAM_INPUT,
        SQL_C_CHAR,
        SQL_VARCHAR,
        sizeof(pesquisa) - 1,
        0,
        pesquisa,
        sizeof(pesquisa),
        &tamanhoPesquisa
    );
    retorno = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(retorno))
    {
        exibirErroODBC(stmt);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return;
    }

    int encontrou = 0;

    printf("\n===== MATERIAS ENCONTRADAS =====\n\n");

    while (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        encontrou = 1;

        SQLGetData(stmt, 1, SQL_C_LONG, &idMateria, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, nomeMateria, sizeof(nomeMateria), NULL);
        SQLGetData(stmt, 3, SQL_C_LONG, &cargaHr, 0, NULL);

        printf("ID: %d\n", idMateria);
        printf("Nome: %s\n", nomeMateria);
        printf("Carga Horaria: %d\n", cargaHr);
        printf("------------------------------\n");
    }

    if (!encontrou)
    {
        printf("Nenhuma materia encontrada.\n");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void atualizarMateria(SQLHDBC conexao, Materia materia)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;
    SQLLEN linhasAfetadas;

    const char sql[] =
        "UPDATE materia SET nome_materia = ?, carga_horaria = ? WHERE id_materia = ?";

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
        materia.nome,
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
        &materia.cargaHr,
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
        &materia.id,
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
            printf("Materia atualizada com sucesso!\n");
        }
        else
        {
            printf("Materia nao encontrada.\n");
        }
    }
    else
    {
        exibirErroODBC(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void excluirMateria(SQLHDBC conexao, int id)
{
    SQLHSTMT stmt;
    SQLRETURN retorno;
    SQLLEN linhasAfetadas;

    const char sql[] =
        "DELETE FROM materia WHERE id_materia = ?";

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
        &id,
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
            printf("Materia excluida com sucesso!\n");
        }
        else
        {
            printf("Materia nao encontrada.\n");
        }
    }
    else
    {
        exibirErroODBC(stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}


