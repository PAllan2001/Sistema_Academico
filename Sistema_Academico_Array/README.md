# Sistema de Cadastro de Alunos em C

Projeto desenvolvido em linguagem C para cadastro e listagem de alunos, utilizando conceitos fundamentais de programação estruturada.

## Objetivo

O sistema permite cadastrar alunos, armazenando:

- Nome
- RA
- Nota

Ao final, o programa exibe uma listagem completa dos alunos cadastrados, mostrando também a situação de cada aluno:

- Aprovado (nota >= 7)
- Reprovado (nota < 7)

Além disso, o sistema realiza validação de RA para impedir cadastros duplicados.

---

# Conceitos utilizados

Este projeto utiliza:

- Variáveis
- Arrays (Vetores)
- Structs
- Estruturas de repetição
- Estruturas condicionais
- Funções
- Validação de dados

---

# Estrutura do Projeto

## Struct

Foi utilizada uma `struct` para representar os dados do aluno:

```c
struct CadAlunos{
    char nome[50];
    int RA;
    float nota;
};

Funções
verificarRA()

Responsável por verificar se um RA já foi cadastrado anteriormente.

listarAlunos()

Responsável por exibir todos os alunos cadastrados e informar a situação de cada um.

Funcionalidades
- Cadastro de alunos
- Validação de RA duplicado
- Listagem completa dos alunos
- Exibição de aprovação/reprovação
- Cadastro contínuo utilizando do while

Tecnologias utilizadas
- Linguagem C
- GCC
- Visual Studio Code

Aprendizados

Durante o desenvolvimento deste projeto foram praticados conceitos importantes da programação estruturada, principalmente:

- Manipulação de arrays
- Uso de funções
- Organização de código
- Validação de dados
- Estruturas de repetição