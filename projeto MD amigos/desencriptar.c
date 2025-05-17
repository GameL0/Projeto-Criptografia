#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


long long int chave_privada(long long int p, long long int q, long long int e)
{
    long long int z = (p - 1) * (q - 1);
    long long int d = 0, a1 = 1, a2 = 0, b1 = 0, b2 = 1, quoc, mod;

    while (e > 0)
    {
        quoc = z / e;
        mod = z % e;

        long long int a = a2 - quoc * a1;
        long long int b = b2 - quoc * b1;

        z = e;
        e = mod;
        a2 = a1;
        a1 = a;
        b2 = b1;
        b1 = b;
    }

    if (z == 1)
    {
        d = a2;
        if (d < 0)
        {
            d += (p - 1) * (q - 1);
        }
    }

    return d;
}

void desencriptar(long long int p, long long int q, long long int e, long long int N)
{
    long long int d = chave_privada(p, q, e);
    N = p * q;
    char mensagem_encriptada[2000];
    scanf(" %1999[^\n]", mensagem_encriptada);

    FILE *arquivo = fopen("mensagem_desencriptada.txt", "w");

    char *aux = strtok(mensagem_encriptada, " ");
    while (aux != NULL)
    {
        long long int valor_criptografado = atoll(aux);

        int valor_desencriptado = 1;
        for (long long int i = 0; i < d; i++)
        {
            valor_desencriptado = (valor_desencriptado * valor_criptografado) % N;
        }

        char caractere_desencriptado = (char)valor_desencriptado;

        fprintf(arquivo, "%c", caractere_desencriptado);

        aux = strtok(NULL, " ");
    }
    fclose(arquivo);

    printf("Mensagem desencriptada com sucesso!");
}

int main()
{
    long long int P, Q, E;
    scanf ("%lld %lld %lld", &P, &Q, &E);
    desencriptar(P, Q, E, 0);
    return 0;
}