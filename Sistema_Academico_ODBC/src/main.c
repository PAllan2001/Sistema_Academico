#include <stdio.h>
#include "aluno.h"
#include "materia.h"
#include "historico.h"
#include "util.h"
#include "conexao.h"

void menuPrincipal()
{
    printf("\n=========================================\n");
    printf("         SISTEMA DE CONTROLE ESCOLAR\n");
    printf("=========================================\n");
    printf("1 - Alunos\n");
    printf("2 - Materias\n");
    printf("3 - Historico\n");
    printf("4 - Sair\n");
    printf("=========================================\n");
    printf("Opcao: ");
}

void menuAlunos(SQLHDBC conexao)
{
    int opcao;
    int ra;
    Aluno aluno;

    do
    {
        printf("\n=========================================\n");
        printf("              MENU ALUNO\n");
        printf("=========================================\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("3 - Buscar aluno por RA\n");
        printf("4 - Atualizar aluno\n");
        printf("5 - Excluir aluno\n");
        printf("6 - Voltar\n");
        printf("=========================================\n");

        opcao = lerInteiro("Opcao: ");

        switch (opcao)
        {
            case 1:
                aluno.ra = lerRA("Digite o RA (6 digitos): ");
                lerTexto("Digite o nome completo: ",
                         aluno.nome,
                         sizeof(aluno.nome));

                cadastrarAluno(conexao, aluno);
                break;

            case 2:
                listarAlunos(conexao);
                break;

            case 3:
                ra = lerRA("Digite o RA: ");
                buscarAlunoPorRA(conexao, ra);
                break;

            case 4:
                aluno.ra = lerRA("Digite o RA do aluno: ");
                lerTexto("Digite o novo nome completo: ",
                         aluno.nome,
                         sizeof(aluno.nome));

                atualizarAluno(conexao, aluno);
                break;

            case 5:
                ra = lerRA("Digite o RA do aluno: ");
                excluirAluno(conexao, ra);
                break;

            case 6:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 6);
}

void menuMaterias(SQLHDBC conexao)
{
    int opcao;
    int id;
    Materia materia;
    char nomeBusca[100];

    do
    {
        printf("\n=========================================\n");
        printf("             MENU MATERIAS\n");
        printf("=========================================\n");
        printf("1 - Cadastrar materia\n");
        printf("2 - Listar materias\n");
        printf("3 - Buscar materia por nome\n");
        printf("4 - Atualizar materia\n");
        printf("5 - Excluir materia\n");
        printf("6 - Voltar\n");
        printf("=========================================\n");

        opcao = lerInteiro("Opcao: ");

        switch (opcao)
        {
            case 1:
                lerTexto("Nome da materia: ",
                         materia.nome,
                         sizeof(materia.nome));

                materia.cargaHr = lerInteiro("Carga horaria: ");

                cadastrarMateria(conexao, materia);
                break;

            case 2:
                listarMaterias(conexao);
                break;

            case 3:
                lerTexto("Digite o nome ou parte do nome: ",
                         nomeBusca,
                         sizeof(nomeBusca));

                buscarMateriaNome(conexao, nomeBusca);
                break;

            case 4:
                materia.id = lerInteiro("ID da materia: ");

                lerTexto("Novo nome da materia: ",
                         materia.nome,
                         sizeof(materia.nome));

                materia.cargaHr = lerInteiro("Nova carga horaria: ");

                atualizarMateria(conexao, materia);
                break;

            case 5:
                id = lerInteiro("ID da materia: ");

                excluirMateria(conexao, id);
                break;

            case 6:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 6);
}
void menuHistorico(SQLHDBC conexao)
{   
    int opcao;
    Historico historico;
    int ra;

    do
    {
        printf("\n=========================================\n");
        printf("            MENU HISTORICO\n");
        printf("=========================================\n");
        printf("1 - Cadastrar historico\n");
        printf("2 - Listar historicos\n");
        printf("3 - Buscar historico por RA\n");
        printf("4 - Voltar\n");
        printf("=========================================\n");
        printf("Opcao: ");

        opcao = lerInteiro("");

        switch (opcao)
        {
        case 1:
        historico.idAluno = lerInteiro("ID do aluno: ");
        historico.idMateria = lerInteiro("ID da materia: ");
        historico.nota = lerNota("Nota (0 a 10): ");

        cadastrarHistorico(conexao, historico);
        break;

    case 2:
        listarHistorico(conexao);
        break;

    case 3:
        ra = lerRA("RA do aluno: ");

        buscarHistoricoRA(conexao, ra);
        break;

    case 4:
        printf("\nVoltando ao menu principal...\n");
        break;

    default:
        printf("\nOpcao invalida.\n");

    } 
    } while (opcao != 4);
}

int main(){
    
    int opcao;
    SQLHDBC conexao = conectarBanco();
do
{
    menuPrincipal();

    opcao = lerInteiro("");

    switch (opcao)
    {
        case 1:
            menuAlunos(conexao);
            break;

        case 2:
            menuMaterias(conexao);
            break;

        case 3:
            menuHistorico(conexao);
            break;

        case 4:
            printf("\nEncerrando o sistema...\n");
            break;

        default:
            printf("\nOpcao invalida.\n");
    }

} while (opcao != 4);

fecharConexao(conexao);

return 0;
 
}