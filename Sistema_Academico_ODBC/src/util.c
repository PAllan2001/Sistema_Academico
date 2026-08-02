#include "util.h"
#include <stdio.h>
#include <string.h>

void limparBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void lerTexto(const char *mensagem, char texto[], int tamanho)
{
    do
    {
        printf("%s", mensagem);

        fgets(texto, tamanho, stdin);

        texto[strcspn(texto, "\n")] = '\0';

        if (strlen(texto) == 0)
        {
            printf("Campo obrigatorio.\n");
        }

    } while (strlen(texto) == 0);
}

int lerInteiro(const char *mensagem)
{
    int valor;

    while (1)
    {
        printf("%s", mensagem);

        if (scanf("%d", &valor) == 1)
        {
            limparBuffer();

            if (valor > 0)
            {
                return valor;
            }

            printf("Digite um numero positivo.\n");
        }
        else
        {
            printf("Digite apenas numeros.\n");
            limparBuffer();
        }
    }
}

int lerNota(const char *mensagem)
{
    int nota;

    while (1)
    {
        nota = lerInteiro(mensagem);

        if (nota >= 0 && nota <= 10)
        {
            return nota;
        }

        printf("A nota deve estar entre 0 e 10.\n");
    }
}

int lerRA(const char *mensagem)
{
    int ra;

    while (1)
    {
        ra = lerInteiro(mensagem);

        if (ra >= 100000 && ra <= 999999)
        {
            return ra;
        }

        printf("O RA deve possuir 6 digitos.\n");
    }
}