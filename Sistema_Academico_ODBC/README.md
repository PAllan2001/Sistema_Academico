# 🎓 Sistema Acadêmico - C + ODBC + SQL Server

Sistema de gerenciamento acadêmico desenvolvido em **C**, utilizando **ODBC** para comunicação com o **SQL Server**.

O projeto foi desenvolvido com o objetivo de aplicar conceitos de programação estruturada, modularização, integração com banco de dados relacional e organização de projetos em múltiplos arquivos.

---

# 📖 Sobre o Projeto

O sistema simula o gerenciamento acadêmico de uma instituição de ensino, permitindo o cadastro de alunos, matérias e históricos escolares através de um sistema CRUD.

Durante o desenvolvimento foram utilizados recursos do ODBC para comunicação com o SQL Server, além de consultas SQL utilizando relacionamentos entre tabelas para apresentar informações completas ao usuário.

O projeto também recebeu uma organização modular, separando a interface do usuário, as operações de banco de dados, a conexão com o banco e as funções de validação de entrada.

---

# 🚀 Tecnologias Utilizadas

- Linguagem C
- SQL Server
- ODBC
- GCC (MinGW)
- Visual Studio Code
- Git
- GitHub

---

# 🗂 Estrutura do Projeto

```
Sistema_Academico_ODBC
│
├── database
│
├── src
│   ├── main.c
│   ├── aluno.c
│   ├── aluno.h
│   ├── materia.c
│   ├── materia.h
│   ├── historico.c
│   ├── historico.h
│   ├── conexao.c
│   ├── conexao.h
│   ├── util.c
│   └── util.h
│
└── README.md
```

---

# ✅ Funcionalidades

## Alunos

- Cadastro de alunos
- Atualização de dados
- Exclusão de alunos
- Busca por RA
- Listagem completa

## Matérias

- Cadastro de matérias
- Atualização de nome e carga horária
- Exclusão de matérias
- Busca por nome utilizando **LIKE**
- Listagem completa

## Histórico Escolar

- Cadastro de histórico
- Consulta completa do histórico
- Consulta do histórico por RA

A listagem do histórico utiliza **INNER JOIN**, exibindo:

- RA
- Nome do aluno
- Nome da matéria
- Nota
- Situação (Aprovado/Reprovado)

A situação é calculada durante a consulta SQL através do comando **CASE**, evitando armazenar informações redundantes no banco de dados.

---

# ✔ Validações Implementadas

O sistema possui funções específicas para validação das entradas do usuário.

### Campos Numéricos

- Não permite letras em campos numéricos.
- Não permite números negativos quando não permitidos.
- Validação específica para notas (0 a 10).
- Validação específica para RA.

### Campos de Texto

- Não permite campos vazios.
- Tratamento para leitura de textos com espaços.

### Banco de Dados

- Utilização de **Prepared Statements**.
- Consultas parametrizadas.
- Verificação de registros encontrados.
- Verificação de linhas afetadas em operações UPDATE e DELETE.

---

# 🗄 Banco de Dados

O sistema utiliza três tabelas relacionais.

## aluno

| Campo | Tipo |
|--------|------|
| id_aluno | INT |
| ra | INT |
| nome_completo | VARCHAR |

---

## materia

| Campo | Tipo |
|--------|------|
| id_materia | INT |
| nome_materia | VARCHAR |
| carga_horaria | INT |

---

## historico

| Campo | Tipo |
|--------|------|
| id_historico | INT |
| id_aluno | FK |
| id_materia | FK |
| nota | INT |

---

# 🔍 Consultas Disponíveis

- Busca de aluno por RA
- Busca de matéria por nome utilizando **LIKE**
- Listagem completa de alunos
- Listagem completa de matérias
- Histórico completo utilizando **INNER JOIN**
- Histórico individual por RA

---

# 🧠 Conceitos Aplicados

- Programação Estruturada
- Modularização em C
- Structs
- ODBC
- SQL Server
- CRUD
- SQL
- Prepared Statements
- SQLBindParameter
- SQLExecute
- SQLFetch
- SQLGetData
- SQLRowCount
- INNER JOIN
- CASE
- Relacionamentos entre tabelas
- Validação de Dados
- Separação de Responsabilidades

---

# 📈 Evolução do Projeto

Durante o desenvolvimento o projeto passou por diversas melhorias, entre elas:

- Separação em múltiplos módulos (.c/.h)
- Criação de uma camada responsável pela conexão com o banco
- Separação das funções de validação em um módulo específico (`util`)
- Remoção da lógica de entrada de dados das funções responsáveis pelo acesso ao banco
- Organização do menu principal e submenus
- Consultas SQL utilizando INNER JOIN
- Implementação de validações para entrada de dados
- Melhor organização da arquitetura do projeto

---

# ▶ Como Executar

1. Clone este repositório.

2. Crie o banco de dados no SQL Server.

3. Execute o script SQL presente na pasta `database`.

4. Configure os parâmetros de conexão no arquivo `conexao.c`.

5. Certifique-se de possuir um Driver ODBC para SQL Server instalado.

6. Compile todos os arquivos `.c`.

Exemplo:

```bash
gcc main.c aluno.c materia.c historico.c util.c conexao.c -o main.exe
```

7. Execute o programa.

---

# 👨‍💻 Autor

**Pablo Allan**

Projeto desenvolvido durante meus estudos de **Programação em C**, **Banco de Dados** e **SQL Server**, com o objetivo de consolidar conceitos de programação estruturada, integração com banco de dados utilizando ODBC e desenvolvimento de aplicações CRUD modulares.