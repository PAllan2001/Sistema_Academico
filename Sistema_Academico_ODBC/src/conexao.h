#ifndef CONEXAO_H
#define CONEXAO_H

#include <windows.h>
#include <sql.h>
#include <sqlext.h>

SQLHDBC conectarBanco(void);
void fecharConexao(SQLHDBC conexao);
void exibirErroODBC(SQLHSTMT stmt);

#endif