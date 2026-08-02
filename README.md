# 🎓 Sistema Acadêmico em C

Este repositório reúne a evolução de um projeto acadêmico desenvolvido durante meus estudos de **Programação em C** e **Banco de Dados**.

O projeto começou como um trabalho da disciplina de **Programação II**, implementando um sistema simples de cadastro de alunos utilizando apenas estruturas de dados em memória. Posteriormente, foi totalmente reestruturado para utilizar **SQL Server** e **ODBC**, transformando-se em um sistema acadêmico completo com persistência de dados e arquitetura modular.

O objetivo deste repositório é demonstrar a evolução da aplicação e do aprendizado ao longo do desenvolvimento.

---

# 📖 Evolução do Projeto

## 📌 Versão 1 — Cadastro de Alunos (Array)

A primeira versão foi desenvolvida como atividade da disciplina de Programação II.

O sistema utilizava apenas recursos da linguagem C para armazenar os dados durante a execução do programa.

### Funcionalidades

- Cadastro de alunos
- Validação de RA duplicado
- Cadastro de nome
- Cadastro de nota
- Listagem dos alunos
- Cálculo da situação (Aprovado/Reprovado)

### Conceitos utilizados

- Programação Estruturada
- Structs
- Arrays
- Funções
- Condicionais
- Laços de repetição
- Manipulação de memória em tempo de execução

Como os dados eram armazenados em memória, todas as informações eram perdidas ao encerrar o programa.

---

## 📌 Versão 2 — Sistema Acadêmico (SQL Server + ODBC)

Na segunda versão, o projeto foi completamente remodelado.

O armazenamento em memória foi substituído por um banco de dados relacional, utilizando **SQL Server** e comunicação através de **ODBC**.

Além disso, o sistema deixou de gerenciar apenas alunos e passou a controlar também matérias e históricos escolares.

### Funcionalidades

#### Alunos

- Cadastro
- Atualização
- Exclusão
- Busca por RA
- Listagem

#### Matérias

- Cadastro
- Atualização
- Exclusão
- Busca por nome utilizando LIKE
- Listagem

#### Histórico

- Cadastro
- Histórico completo
- Histórico por RA

As consultas do histórico utilizam **INNER JOIN**, exibindo:

- RA
- Nome do aluno
- Nome da matéria
- Nota
- Situação (calculada em SQL utilizando CASE)

---

# 🚀 Tecnologias Utilizadas

## Primeira versão

- Linguagem C
- GCC

## Segunda versão

- Linguagem C
- SQL Server
- ODBC
- GCC (MinGW)
- Visual Studio Code

---

# 🧠 Conceitos Aplicados

Durante a evolução do projeto foram praticados conceitos como:

- Programação Estruturada
- Structs
- Modularização
- CRUD
- SQL
- SQL Server
- ODBC
- Prepared Statements
- SQLBindParameter
- SQLExecute
- SQLFetch
- SQLGetData
- SQLRowCount
- INNER JOIN
- CASE
- Relacionamentos entre tabelas
- Validação de entrada de dados
- Separação de responsabilidades

---

# 📈 Principais Evoluções

Comparando as duas versões, foram implementadas diversas melhorias:

- Persistência de dados em banco de dados relacional.
- Separação do projeto em múltiplos módulos (.c/.h).
- Criação de uma camada responsável pela conexão com o banco.
- Separação entre interface, validações e acesso aos dados.
- Utilização de consultas SQL parametrizadas.
- Relacionamentos entre tabelas.
- Consultas utilizando INNER JOIN.
- Busca de matérias utilizando LIKE.
- Histórico acadêmico com cálculo automático da situação do aluno.
- Estrutura preparada para futuras expansões.

---

# 📂 Organização do Repositório

```
/
├── Cadastro_Alunos_Array/          # Primeira versão
│
├── Sistema_Academico_ODBC/         # Segunda versão
│
└── README.md
```

Cada projeto possui seu próprio README com informações específicas sobre implementação, execução e estrutura.

---

# 🎯 Objetivo

Mais do que apresentar um sistema funcional, este repositório demonstra a evolução de uma mesma aplicação ao longo dos estudos, desde uma implementação baseada em arrays até uma versão modular integrada a um banco de dados relacional.

Essa evolução permitiu aplicar conceitos fundamentais da linguagem C e compreender como aplicações reais podem ser estruturadas para facilitar manutenção, escalabilidade e persistência de dados.

---

# 👨‍💻 Autor

**Pablo Allan**

Estudante de Ciência da Computação.

Este repositório reúne projetos desenvolvidos durante minha graduação com o objetivo de consolidar conhecimentos em programação estruturada, banco de dados e desenvolvimento de aplicações em C.