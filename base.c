#include <stdio.h>
#include <unistd.h>   // para getcwd()
#include <sys/stat.h> // para mkdir(), se quiser criar diretórios
#include <limits.h>   // para PATH_MAX

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

            char cwd[PATH_MAX - 32]; // reserva espaço extra para "/chave_publica.txt"
            char path[PATH_MAX];

            if (getcwd(cwd, sizeof(cwd)) != NULL) 
            {
                snprintf(path, sizeof(path), "%s/chave_publica.txt", cwd);


                FILE *numeros = fopen(path, "w");
    
                if (numeros == NULL)
                {
                    printf("Erro ao criar o arquivo.\n");
                    return 1;
                }
    
                fprintf(numeros, "%d %d\n", p, q);
    
                fclose(numeros);
    
                printf("Chave pública salva em '%s'.\n", path);
            }
            else
            {
                perror("Erro ao obter o diretório atual\n");
                return 1;
            }
        }
        
        if (entrada == 2)
        {
            printf("Digite a mensagem de texto a encriptar:\n");
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