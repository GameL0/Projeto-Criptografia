#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long long int modulo_pow(int numero, int numeroE, int numeroD) 
{
    long long int resultado = 1;

    for (int i = 0; i < numeroE; i++) 
    {
        resultado = (resultado * numero) % numeroD;
    }

    return resultado;
}


void escreve_txt(int array[], int tamanhostr, int numeroE, int numeroD)
{
    FILE *arquivo = fopen("mensagem_encriptografada.txt", "w");

    for (int i = 0; i < tamanhostr; i++)
    {
        fprintf(arquivo, "%lld ",  modulo_pow(array[i], numeroE, numeroD));
    }
    

    fclose(arquivo);
}

int main() {

    int numeroE, numeroD;

    scanf("%d %d", &numeroE, &numeroD);

    char string[1000];

    scanf(" %[^\n]", string);

    int tamanhostr = strlen(string);
    int array[tamanhostr];

    for (int i = 0; i < tamanhostr; i++)
    {
        array[i] = string[i];
    }

    escreve_txt(array, tamanhostr, numeroE, numeroD);


    printf("Chave encriptada com sucesso");

    return  0;
}
