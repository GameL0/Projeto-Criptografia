#include <stdio.h>
#include <unistd.h>   // para getcwd()
#include <limits.h>   // para PATH_MAX
#include <math.h>    // para sqrt()

int verificar_primo(long long a){
    if (a < 2) return 0; // menores que 2 não são primos

    if (a == 2 || a == 3) return 1; // 2 e 3 são primos

    if (a % 2 == 0 || a % 3 == 0) return 0; // elimina pares e múltiplos de 3

    long long limite = (long long) sqrt((double)a);

    for (long long i = 5; i <= limite; i += 6) {
        if (a % i == 0 || a % (i + 2) == 0)
        return 0;
    }
    return 1;
}

int verificar_coprimo(long long int aux, long long int z) 
{
    for (long long int i = 2; i * i <= z; i++)
    {
        if (aux % i == 0 || z % i == 0)
        {
            long long int num = aux / i;
            long long int numz = z / i;
            return (num != numz);
        } 
    }
    return 1;
}

long long int mdc(long long a, long long b)
{
    while(a % b != 0)
    {
        temp = b;
        b = a % b;
        a = b;
    }
    return b;
}



int main()
{
    printf("Digite um número de 1 a 3:\n");
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
            long long int p, q, z, e;
            printf("Digite um par de números primos (p e q):\n");
            scanf("%lld %lld", &p, &q);
            
            while (!verificar_primo(p) || !verificar_primo(q)) 
            {
            printf("Os números inseridos são inválidos. Por favor, digite dois números PRIMOS novamente\n");
            scanf("%lld %lld", &p, &q);
            }
        
        n = p * q; // n é usado na chave pública
        z = (p - 1) * (q - 1); // z é usado na chave privada phi(n)
        
        
        printf("\nDigite um expoente coprimo a (p - 1)(q - 1):\n");
        // le o expoente publico e (deve ser coprimo de z)
        scanf("%lld\n", &e);

        while (e <= 1 || e >= z || !gcd(e, z)) 
        {
            printf("O numero inserido não é coprimo, por favor digite outro número\n");
            scanf("%lld", &e);
        }

        while(mdc(e)!=1)

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
            // receber mensagem de texto
            
=======
            printf("\n");

>>>>>>> ff25afeeb7866ed2f1471723105b0e206dbc8225
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