#include <stdio.h>

int main()
{
    int entrada;
    scanf("%d", &entrada);
    if (entrada < 1 || entrada > 3)
    {
        printf("Opção inválida\n");
        return 0;
    }

    else
    {
        if (entrada == 1)
        {
            int p, q;
            printf("Digite um par de números primos (p e q):\n");
            scanf("%d %d", &p, &q);

            int e;
            printf("\n");
            printf("Digite um expoente relativamente primo a (p - 1)(q - 1):\n");
            scanf("%d", &e);
            printf("\n");
        }
        
        if (entrada == 2)
        {
            
            printf("Digite a mensagem de texto a encriptar:\n");
            scanf("%s", &???????);
            printf("\n");
        }

        if (entrada == 3)
        {
            int p, q;
            printf("Digite um par de números primos (p e q):\n");
            scanf("%d %d", &p, &q);

            int e;
            printf("\n");
            printf("Digite um expoente relativamente primo a (p - 1)(q - 1):\n");
            scanf("%d", &e);
            printf("\n");
        }
    }
}