#include "conexao.h"
#include <stdio.h>

SQLHDBC conectarBanco(void)
{
    SQLHENV ambiente;
    SQLHDBC conexao;
    SQLRETURN retorno;

    SQLCHAR stringConexao[] =
        "Driver={ODBC Driver 17 for SQL Server};"
        "Server=Host,Codigo;"
        "Database=NomeBD;"
        "Uid=usuario;"
        "Pwd=senha;"
        "Encrypt=Yes;"
        "TrustServerCertificate=Yes;";

    SQLCHAR stringRetorno[1024];
    SQLSMALLINT tamanhoRetorno;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &ambiente);

    SQLSetEnvAttr(
        ambiente,
        SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3,
        0
    );

    SQLAllocHandle(SQL_HANDLE_DBC, ambiente, &conexao);

    retorno = SQLDriverConnect(
        conexao,
        NULL,
        stringConexao,
        SQL_NTS,
        stringRetorno,
        sizeof(stringRetorno),
        &tamanhoRetorno,
        SQL_DRIVER_COMPLETE
    );
/*TESTE DE CONEXAO

    SQLCHAR estadoSQL[6];
    SQLINTEGER codigoErro;
    SQLCHAR mensagemErro[256];
    SQLSMALLINT tamanhoMensagem;

    if (SQL_SUCCEEDED(retorno))
    {
        printf("Conexao realizada com sucesso!\n");
    }
    else
    {
        printf("Erro ao conectar ao banco!\n");
        SQLGetDiagRec(
                SQL_HANDLE_DBC,
            conexao,
            1,
            estadoSQL,
            &codigoErro,
            mensagemErro,
            sizeof(mensagemErro),
            &tamanhoMensagem
        );
    }
*/
    return conexao;
}

void fecharConexao(SQLHDBC conexao)
{
    if (conexao != NULL)
    {
        SQLDisconnect(conexao);
        SQLFreeHandle(SQL_HANDLE_DBC, conexao);
    }
}
void exibirErroODBC(SQLHSTMT stmt)
{
    SQLCHAR estadoSQL[6];
    SQLCHAR mensagemErro[256];
    SQLINTEGER codigoErro;
    SQLSMALLINT tamanhoMensagem;
    SQLRETURN retorno;
    int registro = 1;

    while ((retorno = SQLGetDiagRec(
                SQL_HANDLE_STMT,
                stmt,
                registro,
                estadoSQL,
                &codigoErro,
                mensagemErro,
                sizeof(mensagemErro),
                &tamanhoMensagem
            )) == SQL_SUCCESS)
    {
        printf(
            "Erro ODBC [%s] (%ld): %s\n",
            estadoSQL,
            (long)codigoErro,
            mensagemErro
        );

        registro++;
    }
}