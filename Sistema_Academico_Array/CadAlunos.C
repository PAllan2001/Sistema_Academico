#include <stdio.h>
#define MAX_ALUNOS 100


struct CadAlunos
{
    char nome[50];
    int RA;
    float nota;
};

int verificarRA(struct CadAlunos alunos[], int quantidade, int RA){

    for(int i = 0; i < quantidade; i++){

        if(alunos[i].RA == RA){
            return 1;
        }
    }

    return 0;
}



void listarAlunos(struct  CadAlunos alunos[], int quantidade){
    
    printf("\n======= LISTA DE ALUNOS ======\n");
    for(int i = 0; i < quantidade; i++){

        printf("\nAluno %d\n", i + 1 );

        printf("Nome: %s\n", alunos[i].nome);
        printf("RA: %d\n",alunos[i].RA);
        printf("Nota: %.2f\n",alunos[i].nota);

        if(alunos[i].nota >= 7){
            printf("Aprovado\n");
        }
        else{
            printf("Reprovado\n");
        }
    }
}

int main(){
    struct CadAlunos alunos[MAX_ALUNOS];
    int quantidade = 0;
    char continuar;
    

    do{

    printf("\n Cadastro do Aluno %d\n ", quantidade + 1);

    do{

    printf("RA: ");
    scanf("%d", &alunos[quantidade].RA);

    if(verificarRA (alunos, quantidade, alunos[quantidade].RA)){
        printf("RA ja cadastrado! Digite outro.\n");
    }

        }while(verificarRA(alunos, quantidade, alunos[quantidade].RA));
         
        scanf("%c", &continuar);

        printf("Nome: ");
        scanf("%[^\n]", alunos[quantidade].nome);
        
        printf("Nota: ");
        scanf("%f", &alunos[quantidade].nota);

        quantidade++;

        scanf("%c", &continuar);

        if (quantidade < MAX_ALUNOS)
        {
            printf("Deseja cadastrar outro aluno? (s/n): ");
            scanf("%c", &continuar);
        } else {
            printf("\nLimite maximo de alunos atigindo!\n");
            continuar = 'n';
        }
        
    }while(continuar == 's');

    listarAlunos(alunos,quantidade);
    
    return 0;   
}